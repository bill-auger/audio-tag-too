
#include "JuceBoilerplateStore.h"
#include "Seeds.h"
#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/StorageConstants.h"
#include "../Trace/TraceJuceBoilerplateStore.h"


/* JuceBoilerplateStore public instance methods */

JuceBoilerplateStore::~JuceBoilerplateStore()
{
  File storage_dir      = APP::AppdataDir().getChildFile(STORE::STORAGE_DIRNAME ) ;
  this->storageFile     = storage_dir      .getChildFile(STORE::STORAGE_FILENAME) ;
  this->deviceFile      = storage_dir      .getChildFile(STORE::DEVICE_FILENAME ) ;
  this->peaksCacheFile  = storage_dir      .getChildFile(STORE::PEAKS_FILENAME  ) ;
  this->storageTempFile = storage_dir      .getChildFile(APP:APP_CMD + ".temp") ;
}


/* JuceBoilerplateStore private instance methods */

/* initialization */

JuceBoilerplateStore::JuceBoilerplateStore() { }

bool JuceBoilerplateStore::initialize()
{
  // create shared config ValueTree from persistent storage or defaults
  loadConfig() ; verifyConfig() ;

  listen(true) ;

  return true ;
}

void JuceBoilerplateStore::teardown() { listen(false) ; storeConfig(this->deviceStateXml.get()) ; }


/* persistence */

void JuceBoilerplateStore::loadConfig()
{
  // load application configuration from persistent storage
#ifdef STORAGE_IS_BINARY
  FileInputStream* storage = new FileInputStream(this->storageFile) ;
  this->root               = (storage->openedOk()) ? ValueTree::readFromStream(*storage) :
                                                     ValueTree::invalid                  ;
  delete storage ;
#else // STORAGE_IS_BINARY
  XmlElement* storage_xml  = XmlDocument::parse(this->storageFile) ;
  this->root               = (storage_xml != nullptr) ? ValueTree::fromXml(*storage_xml) :
                                                        ValueTree::invalid               ;
  delete storage_xml ;
#endif // STORAGE_IS_BINARY

  // load audio device configuration from persistent storage
  this->deviceStateXml.reset(XmlDocument::parse(this->deviceFile)) ;
  bool is_config_valid = (this->deviceStateXml.get() != nullptr                      &&
                          this->deviceStateXml.get()->hasTagName(STORE::DEVICE_XML_ID)) ;
  if (!is_config_valid) this->deviceStateXml.reset() ;
}

bool JuceBoilerplateStore::storeConfig(XmlElement* device_state_xml)
{
DEBUG_TRACE_STORE_CONFIG

  // prepare storage directory
  if (this->storageTempFile.create().failed() || !this->storageTempFile.deleteFile())
  {
    Trace::TraceError(GUI::FILESYSTEM_WRITE_ERROR_MSG) ;
    return false ;
  }

DEBUG_TRACE_DUMP_STORE(this->root , "root")

  if (this->root.isValid())
  {
#ifdef STORAGE_IS_BINARY

DEBUG_WRITE_STORE_XML(this->root , "root")

    // marshall application configuration out to persistent binary storage
    FileOutputStream* storage_stream = new FileOutputStream(this->storageTempFile) ;
    if (!storage_stream->failedToOpen())
    {
      this->root.writeToStream(*storage_stream) ;
      storage_stream->flush() ;
      this->storageTempFile.moveFileTo(this->storageFile) ;
      delete storage_stream ;
    }
    else
    {
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
      delete storage_stream ;

      return false ;
    }

#else // STORAGE_IS_BINARY

    // marshall application configuration out to persistent XML storage
    XmlElement* storage_xml = this->root.createXml() ;
    if (storage_xml->writeToFile(this->storageFile , StringRef() , StringRef("UTF-8") , 0))
      delete storage_xml ;
    else
    {
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
      delete storage_xml ;

      return false ;
    }

#endif // STORAGE_IS_BINARY
  }

  // marshall audio device configuration out to persistent XML storage
  if (device_state_xml != nullptr)
  {
    if (device_state_xml->writeToFile(this->storageTempFile , String::empty))
    {
      this->deviceStateXml.reset(device_state_xml) ;
      this->storageTempFile.moveFileTo(this->deviceFile) ;
      delete device_state_xml ;
    }
    else
    {
      if (device_state_xml != this->deviceStateXml.get()) delete device_state_xml ;
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "audio device configuration") ;

      return false ;
    }
  }

  return true ;
}


/* validations */

void JuceBoilerplateStore::verifyConfig()
{
  // verify or reset stored configuration
  bool was_storage_found   = this->root.isValid() ;
  bool is_root_valid       = this->root.hasType(STORE::STORAGE_ID) ;
  bool has_canonical_nodes = !hasDuplicatedNodes(this->root) ;
  if      (!was_storage_found || !is_root_valid) this->root = Seeds::DefaultStore() ;
  else if (!has_canonical_nodes                ) removeConflictedNodes(this->root , String::empty) ;

  // verify schema version
  int  stored_version    = int(this->root[STORE::CONFIG_VERSION_KEY]) ;
  bool do_versions_match = stored_version == STORE::CONFIG_VERSION ;
  if (!do_versions_match)
  {
    // NYI: convert (if ever necessary)
    File parent_dir  = this->storageFile.getParentDirectory() ;
    File backup_file = parent_dir.getNonexistentChildFile(STORE::STORAGE_FILENAME , ".bak" , false) ;
    this->storageFile.copyFileTo(backup_file) ;

    this->root.removeProperty(STORE::CONFIG_VERSION_KEY , nullptr) ;
  }

DEBUG_TRACE_VERIFY_STORED_CONFIG
}

void JuceBoilerplateStore::verifyRoot()
{
  // ensure missing properties exist
  verifyRootProperty(STORE::CONFIG_VERSION_KEY , var(STORE::CONFIG_VERSION)) ;
}

void JuceBoilerplateStore::sanitizeRoot()
{
  // filter any rogue data
  filterRogueKeys (this->root , STORE::RootPersistentKeys ()) ;
  filterRogueNodes(this->root , STORE::RootPersistentNodes()) ;
}


/* validation/sanitization helpers */

void JuceBoilerplateStore::verifyChildNode(ValueTree store , Identifier node_id)
{
DEBUG_TRACE_VERIFY_MISSING_NODE

  if (!store.getChildWithName(node_id).isValid())
    store.addChild(ValueTree(node_id) , -1 , nullptr) ;
}

void JuceBoilerplateStore::verifyRootChildNode(Identifier node_id)
{
  verifyChildNode(this->root , node_id) ;
}

void JuceBoilerplateStore::verifyProperty(ValueTree store , Identifier key , var default_value)
{
DEBUG_TRACE_VERIFY_MISSING_PROPERTY

  if (!store.hasProperty(key)) store.setProperty(key , default_value , nullptr) ;
}

void JuceBoilerplateStore::verifyRootProperty(Identifier key , var default_value)
{
  verifyProperty(this->root , key , default_value) ;
}

bool JuceBoilerplateStore::hasDuplicatedNodes(ValueTree stored_config)
{
  StringArray root_node_ids      = STORE::RootPersistentNodes() ;
  int         n_duplicated_nodes = 0 ;
  bool        has_duplicates     = false ;

  n_duplicated_nodes = nDuplicatedNodes(stored_config , root_node_ids) ;
  has_duplicates     = has_duplicates || n_duplicated_nodes > root_node_ids.size() ;

  return has_duplicates ;
}

int JuceBoilerplateStore::nDuplicatedNodes(ValueTree parent_node , StringArray node_ids)
{
  int n_duplicated_nodes = 0 ;

  for (int node_n = 0 ; node_n < node_ids.size() ; ++node_n)
  {
    Identifier node_id = STORE::FilterId(node_ids[node_n]) ;

    for (int child_n = 0 ; child_n < parent_node.getNumChildren() ; ++child_n)
      if (parent_node.getChild(child_n).hasType(node_id)) ++n_duplicated_nodes ;
  }

  return n_duplicated_nodes ;
}

void JuceBoilerplateStore::removeConflictedNodes(ValueTree parent_node , Identifier node_id)
{
  ValueTree node ;
  while ((node = parent_node.getChildWithName(node_id)).isValid())
    parent_node.removeChild(node , nullptr) ;
}

void JuceBoilerplateStore::filterRogueKeys(ValueTree parent_node , StringArray persistent_keys)
{
  for (int key_n = 0 ; key_n < parent_node.getNumProperties() ; ++key_n)
  {
    String property_id = STRING(parent_node.getPropertyName(key_n)) ;

DEBUG_TRACE_FILTER_ROGUE_KEY

    if (!persistent_keys.contains(property_id))
      parent_node.removeProperty( property_id , nullptr) ;
  }
}

void JuceBoilerplateStore::filterRogueNodes(ValueTree parent_node , StringArray persistent_node_ids)
{
  for (int child_n = 0 ; child_n < parent_node.getNumChildren() ; ++child_n)
  {
    String node_id = STRING(parent_node.getChild(child_n).getType()) ;

DEBUG_TRACE_FILTER_ROGUE_NODE

    if (!persistent_node_ids.contains(node_id))
      parent_node.removeChild(child_n , nullptr) ;
  }
}

void JuceBoilerplateStore::sanitizeIntProperty(ValueTree store     , Identifier key      ,
                                               int       min_value , int        max_value)
{
  int value = int(store[key]) ;

  if (value < min_value || value > max_value) store.removeProperty(key , nullptr) ;

DEBUG_TRACE_SANITIZE_INT_PROPERTY
}

void JuceBoilerplateStore::sanitizeComboProperty(ValueTree   store   , Identifier key ,
                                                 StringArray options                  )
{
  sanitizeIntProperty(store , key , 0 , options.size() - 1) ;
}


/* event handlers */

void JuceBoilerplateStore::listen(bool should_listen)
{
DEBUG_TRACE_LISTEN

  if (should_listen) { this->root.addListener   (this) ; }
  else               { this->root.removeListener(this) ; }
}

void JuceBoilerplateStore::valueTreePropertyChanged(ValueTree& node , const Identifier& key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED
}


/* getters/setters */

bool JuceBoilerplateStore::isKnownProperty(ValueTree node , const Identifier& key)
{
  ValueTree parent_node = node.getParent() ;

  return (node == this->root) ? STORE::RootKeys().contains(key) :
                                false                           ;
}

void JuceBoilerplateStore::setProperty(ValueTree node  , const Identifier& key ,
                                       const var value                         )
{
DEBUG_TRACE_SET_PROPERTY

  if (node.isValid()) node.setProperty(key , value , nullptr) ;
}

bool JuceBoilerplateStore::setConfig(ValueTree config_node , const Identifier& key ,
                                     const var value                               )
{
DEBUG_TRACE_SET_CONFIG

  // validate mutating of critical configuration
  bool is_valid = config_node == this->root && isKnownProperty(config_node , key) ;

  if (is_valid) setProperty(config_node , key , value) ;

  return is_valid ;
}