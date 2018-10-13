/*\
|*|  AudioTagToo - Clip and stitch audio samples
|*|  Copyright 2018 bill-auger <https://github.com/bill-auger/audio-tag-too/issues>
|*|
|*|  This file is part of the AudioTagToo program.
|*|
|*|  AudioTagToo is free software: you can redistribute it and/or modify
|*|  it under the terms of the GNU General Public License as published by
|*|  the Free Software Foundation, either version 3 of the License, or
|*|  (at your option) any later version.
|*|
|*|  AudioTagToo is distributed in the hope that it will be useful,
|*|  but WITHOUT ANY WARRANTY; without even the implied warranty of
|*|  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|*|  GNU General Public License for more details.
|*|
|*|  You should have received a copy of the GNU General Public License
|*|  along with AudioTagToo.  If not, see <http://www.gnu.org/licenses/>.
\*/


#include "AudioTagTooStore.h"
#include "Seeds.h"
#include "../Constants/AppConstants.h"
#include "../Constants/GuiConstants.h"
#include "../Constants/StorageConstants.h"
#include "../Trace/TraceAudioTagTooStore.h"


/* AudioTagTooStore public instance methods */

AudioTagTooStore::~AudioTagTooStore() { }


/* AudioTagTooStore private instance methods */

/* initialization */

AudioTagTooStore::AudioTagTooStore() { }

bool AudioTagTooStore::initialize()
{
  // create shared config ValueTree from persistent storage or defaults
  loadConfig() ; verifyConfig() ;

  listen(true) ;

  return true ;
}

void AudioTagTooStore::teardown() { listen(false) ; storeConfig(this->deviceStateXml.get()) ; }


/* validations */

void AudioTagTooStore::verifyConfig()
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

  this->clips        = this->root.getOrCreateChildWithName(STORE::CLIPS_ID        , nullptr) ;
  this->compilations = this->root.getOrCreateChildWithName(STORE::COMPILATIONS_ID , nullptr) ;

DEBUG_TRACE_VERIFY_STORED_CONFIG
}

void AudioTagTooStore::verifyRoot()
{
  // ensure missing properties exist
  verifyRootProperty(STORE::CONFIG_VERSION_KEY , var(STORE::CONFIG_VERSION)) ;
}

void AudioTagTooStore::sanitizeRoot()
{
  // filter any rogue data
  filterRogueKeys (this->root , STORE::RootPersistentKeys ()) ;
  filterRogueNodes(this->root , STORE::RootPersistentNodes()) ;
}

/* validation/sanitization helpers */

void AudioTagTooStore::verifyChildNode(ValueTree store , Identifier node_id)
{
DEBUG_TRACE_VERIFY_MISSING_NODE

  if (!store.getChildWithName(node_id).isValid())
    store.addChild(ValueTree(node_id) , -1 , nullptr) ;
}

void AudioTagTooStore::verifyRootChildNode(Identifier node_id)
{
  verifyChildNode(this->root , node_id) ;
}

void AudioTagTooStore::verifyProperty(ValueTree store , Identifier key , var default_value)
{
DEBUG_TRACE_VERIFY_MISSING_PROPERTY

  if (!store.hasProperty(key)) store.setProperty(key , default_value , nullptr) ;
}

void AudioTagTooStore::verifyRootProperty(Identifier key , var default_value)
{
  verifyProperty(this->root , key , default_value) ;
}

bool AudioTagTooStore::hasDuplicatedNodes(ValueTree stored_config)
{
  StringArray root_node_ids      = STORE::RootPersistentNodes() ;
  int         n_duplicated_nodes = 0 ;
  bool        has_duplicates     = false ;

  n_duplicated_nodes = nDuplicatedNodes(stored_config , root_node_ids) ;
  has_duplicates     = has_duplicates || n_duplicated_nodes > root_node_ids.size() ;

  return has_duplicates ;
}

int AudioTagTooStore::nDuplicatedNodes(ValueTree parent_node , StringArray node_ids)
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

void AudioTagTooStore::removeConflictedNodes(ValueTree parent_node , Identifier node_id)
{
  ValueTree node ;
  while ((node = parent_node.getChildWithName(node_id)).isValid())
    parent_node.removeChild(node , nullptr) ;
}

void AudioTagTooStore::filterRogueKeys(ValueTree parent_node , StringArray persistent_keys)
{
  for (int key_n = 0 ; key_n < parent_node.getNumProperties() ; ++key_n)
  {
    String property_id = STRING(parent_node.getPropertyName(key_n)) ;

DEBUG_TRACE_FILTER_ROGUE_KEY

    if (!persistent_keys.contains(property_id))
      parent_node.removeProperty( property_id , nullptr) ;
  }
}

void AudioTagTooStore::filterRogueNodes(ValueTree parent_node , StringArray persistent_node_ids)
{
  for (int child_n = 0 ; child_n < parent_node.getNumChildren() ; ++child_n)
  {
    String node_id = STRING(parent_node.getChild(child_n).getType()) ;

DEBUG_TRACE_FILTER_ROGUE_NODE

    if (!persistent_node_ids.contains(node_id))
      parent_node.removeChild(child_n , nullptr) ;
  }
}

void AudioTagTooStore::sanitizeIntProperty(ValueTree store     , Identifier key      ,
                                           int       min_value , int        max_value)
{
  int value = int(store[key]) ;

  if (value < min_value || value > max_value) store.removeProperty(key , nullptr) ;

DEBUG_TRACE_SANITIZE_INT_PROPERTY
}

void AudioTagTooStore::sanitizeComboProperty(ValueTree   store   , Identifier key ,
                                             StringArray options                  )
{
  sanitizeIntProperty(store , key , 0 , options.size() - 1) ;
}


/* persistence */

void AudioTagTooStore::loadConfig()
{
  // load application configuration from persistent storage
  File storage_dir         = APP::AppdataDir().getChildFile(STORE::STORAGE_DIRNAME ) ;
  this->deviceXmlFile      = storage_dir      .getChildFile(STORE::DEVICE_FILENAME ) ;
#ifdef STORAGE_IS_BINARY
  this->storageFile        = storage_dir      .getChildFile(STORE::STORAGE_FILENAME) ;
  FileInputStream* storage = new FileInputStream(this->storageFile) ;
  this->root               = (storage->openedOk()) ? ValueTree::readFromStream(*storage) :
                                                     ValueTree::invalid                  ;
  delete storage ;
#else // STORAGE_IS_BINARY
  this->storageFile        =
  this->storageXmlFile     = storage_dir      .getChildFile(STORE::STORAGE_FILENAME) ;
  XmlElement* storage_xml  = XmlDocument::parse(this->storageXmlFile) ;
  this->root               = (storage_xml != nullptr) ? ValueTree::fromXml(*storage_xml) :
                                                        ValueTree::invalid               ;
  delete storage_xml ;
#endif // STORAGE_IS_BINARY

  // load audio device configuration from persistent storage
  this->deviceStateXml.reset(XmlDocument::parse(this->deviceXmlFile)) ;
  bool is_config_valid = (this->deviceStateXml.get() != nullptr                      &&
                          this->deviceStateXml.get()->hasTagName(STORE::DEVICE_XML_ID)) ;
  if (!is_config_valid) this->deviceStateXml.reset() ;
}

bool AudioTagTooStore::storeConfig(XmlElement* device_state_xml)
{
DEBUG_TRACE_STORE_CONFIG

  // prepare storage directory
  File temp_file = this->storageFile.getSiblingFile(STORE::STORAGE_FILENAME + ".temp") ;
  if (temp_file.create().failed() || !temp_file.deleteFile())
  {
#ifdef HAS_MAIN_CONTROLLER
    AudioTagToo::Error(GUI::FILESYSTEM_WRITE_ERROR_MSG) ;
#else // HAS_MAIN_CONTROLLER
    Trace::TraceError(GUI::FILESYSTEM_WRITE_ERROR_MSG) ;
#endif // HAS_MAIN_CONTROLLER

    return false ;
  }

DEBUG_TRACE_DUMP_STORE(this->root , "root")

  if (this->root.isValid())
  {
#ifdef STORAGE_IS_BINARY

DEBUG_WRITE_STORE_XML(this->root , "root")

    // marshall application configuration out to persistent binary storage
    FileOutputStream* storage_stream = new FileOutputStream(temp_file) ;
    if (!storage_stream->failedToOpen())
    {
      this->root.writeToStream(*storage_stream) ;
      storage_stream->flush() ;
      temp_file.moveFileTo(this->storageFile) ;
      delete storage_stream ;
    }
    else
    {
  #ifdef HAS_MAIN_CONTROLLER
      AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
  #else // HAS_MAIN_CONTROLLER
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
  #endif // HAS_MAIN_CONTROLLER
      delete storage_stream ;

      return false ;
    }

#else // STORAGE_IS_BINARY

    // marshall application configuration out to persistent XML storage
    XmlElement* storage_xml = this->root.createXml() ;
    if (storage_xml->writeToFile(this->storageXmlFile , StringRef() , StringRef("UTF-8") , 0))
      delete storage_xml ;
    else
    {
#ifdef HAS_MAIN_CONTROLLER
      AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
#else // HAS_MAIN_CONTROLLER
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
#endif // HAS_MAIN_CONTROLLER
      delete storage_xml ;

      return false ;
    }

#endif // STORAGE_IS_BINARY
  }

  // marshall audio device configuration out to persistent XML storage
  if (device_state_xml != nullptr)
  {
    if (device_state_xml->writeToFile(temp_file , String::empty))
    {
      this->deviceStateXml.reset(device_state_xml) ;
      temp_file.moveFileTo(this->deviceXmlFile) ;
      delete device_state_xml ;
    }
    else
    {
      if (device_state_xml != this->deviceStateXml.get()) delete device_state_xml ;
#ifdef HAS_MAIN_CONTROLLER
      JuceBoilerplate::Error(GUI::STORAGE_WRITE_ERROR_MSG + "audio device configuration") ;
#else // HAS_MAIN_CONTROLLER
      Trace::TraceError(GUI::STORAGE_WRITE_ERROR_MSG + "audio device configuration") ;
#endif // HAS_MAIN_CONTROLLER

      return false ;
    }
  }

  return true ;
}


/* event handlers */

void AudioTagTooStore::listen(bool should_listen)
{
#ifdef HAS_MAIN_CONTROLLER
  if (!AudioTagToo::IsInitialized) return ;
#endif // HAS_MAIN_CONTROLLER

DEBUG_TRACE_LISTEN

  if (should_listen) { this->root.addListener   (this) ; }
  else               { this->root.removeListener(this) ; }
}

void AudioTagTooStore::valueTreePropertyChanged(ValueTree& node , const Identifier& key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

#ifdef HAS_MAIN_CONTROLLER
  AudioTagToo::HandleConfigChanged(key) ;
#endif // HAS_MAIN_CONTROLLER
}


/* getters/setters */

bool AudioTagTooStore::isKnownProperty(ValueTree node , const Identifier& key)
{
  ValueTree parent_node = node.getParent() ;

  return (node == this->root) ? STORE::RootKeys().contains(key) :
                                false                           ;
}

void AudioTagTooStore::setProperty(ValueTree node  , const Identifier& key ,
                                   const var value                         )
{
DEBUG_TRACE_SET_PROPERTY

  if (node.isValid()) node.setProperty(key , value , nullptr) ;
}

void AudioTagTooStore::setConfig(ValueTree config_node , const Identifier& key ,
                                 const var value                               )
{
DEBUG_TRACE_SET_CONFIG

  // validate mutating of critical configuration
  if (!config_node.isValid() || !isKnownProperty(config_node , key)) return ;

#ifdef HAS_MAIN_CONTROLLER

  if (!AudioTagToo::IsInitialized || !AudioTagToo::DisabledFeatures.contains(key))
#endif // HAS_MAIN_CONTROLLER
    setProperty(config_node , key , value) ;
}

void AudioTagTooStore::createClip(String& audio_filename , double begin_time , double end_time)
{
  Identifier master_id = STORE::FilterId(audio_filename) ;
  Identifier clip_id   = STORE::FilterId(audio_filename     + '-' +
                                         String(begin_time) + '-' +
                                         String(end_time  )       ) ;

  ValueTree master_store    = this->clips.getChildWithName(master_id) ;
  bool      is_new_master   = !master_store.isValid() ;
  var       master_filename = master_store.getProperty(STORE::FILENAME_KEY) ;
  bool      is_id_collision = !is_new_master && STRING(master_filename) != audio_filename ;

DEBUG_TRACE_CREATE_CLIP

  if (!is_id_collision)
  {
    // create new clip (creating and appending a new master to the tree if necessary)
    master_store         = this->clips.getOrCreateChildWithName(master_id , nullptr) ;
    ValueTree clip_store = ValueTree(clip_id) ;

    // set clip properties and append it to the master source entry
    setProperty(clip_store , STORE::FILENAME_KEY   , audio_filename) ;
    setProperty(clip_store , STORE::BEGIN_TIME_KEY , begin_time    ) ;
    setProperty(clip_store , STORE::END_TIME_KEY   , end_time      ) ;
    master_store.appendChild(clip_store , nullptr) ;

    // sort masters and clips
    STORE::IdComparator<ValueTree&> id_comparator ;
    this->clips .sort(id_comparator , nullptr , false) ;
    master_store.sort(id_comparator , nullptr , false) ;
  }
  else return ; // TODO: collision alert
}
