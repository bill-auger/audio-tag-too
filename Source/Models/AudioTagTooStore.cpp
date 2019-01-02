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
#include "../Controllers/AudioTagToo.h"
#ifdef CONTROLLER_OWNS_STORAGE
#include "../Views/MainContent.h"
#endif // CONTROLLER_OWNS_STORAGE
#include "../Trace/TraceAudioTagTooStore.h"


/* AudioTagTooStore public instance methods */

/* setup/teardown */

AudioTagTooStore::AudioTagTooStore() : thumbnailCache(GUI::CACHE_N_THUMBS)
{
  File storage_dir      = APP::AppdataDir().getChildFile(STORE::STORAGE_DIRNAME ) ;
  this->storageFile     = storage_dir      .getChildFile(STORE::STORAGE_FILENAME) ;
  this->deviceFile      = storage_dir      .getChildFile(STORE::DEVICE_FILENAME ) ;
  this->peaksCacheFile  = storage_dir      .getChildFile(STORE::PEAKS_FILENAME  ) ;
  this->storageTempFile = storage_dir      .getChildFile(APP::APP_CMD + ".temp" ) ;

  // create shared config ValueTree from persistent storage or defaults
  loadConfig() ; verifyConfig() ;

DEBUG_PRIME_CLIPS_STORAGE

#ifndef CONTROLLER_OWNS_STORAGE
  listen(true) ;
#endif // CONTROLLER_OWNS_STORAGE
}

AudioTagTooStore::~AudioTagTooStore() { listen(false) ; storeConfig() ; }


/* public getters/setters */

bool AudioTagTooStore::setProperty(ValueTree node  , const Identifier& key ,
                                   const var value                         )
{
  bool is_valid = node.isValid() ;

DEBUG_TRACE_SET_PROPERTY

  if (is_valid) node.setProperty(key , value , nullptr) ;

  return is_valid ;
}

bool AudioTagTooStore::setConfig(ValueTree config_node , const Identifier& key ,
                                 const var value                               )
{
DEBUG_TRACE_SET_CONFIG

  // verify mutation of critical configuration
  bool is_valid_config_node_and_key = isConfigProperty(config_node , key) ;

  if (is_valid_config_node_and_key) setProperty(config_node , key , value) ;

  return is_valid_config_node_and_key ;
}

ValueTree AudioTagTooStore::getChildNodeById(ValueTree root_store , Identifier node_id)
{
  ValueTree child_node ;

  if ((child_node = root_store.getChildWithName(node_id)).isValid())
    return child_node ;
  else for (int master_n = 0 ; master_n < root_store.getNumChildren() ; ++master_n)
    if ((child_node = root_store.getChild(master_n).getChildWithName(node_id)).isValid())
      return child_node ;

  return ValueTree::invalid ;
}

ValueTree AudioTagTooStore::createClip(String audio_filename , double begin_time , double end_time)
{
  // validate clip params
  Identifier master_id         = STORE::FilterId(audio_filename) ;
  Identifier clip_id           = STORE::FilterId(audio_filename     + '-' +
                                                 String(begin_time) + '-' +
                                                 String(end_time  )       ) ;
  ValueTree  master_node       = this->clips.getChildWithName(master_id) ;
  String     existing_filename = STRING(master_node[STORE::FILENAME_KEY]) ;
  bool       is_new_master     = !master_node.isValid() ;
  bool       does_file_exist   = File(audio_filename).existsAsFile() ;
  bool       is_valid_length   = end_time - begin_time > 0.0 ;
  bool       is_id_collision   = !is_new_master && existing_filename != audio_filename ;
  bool       is_duplicate_clip = master_node.getChildWithName(clip_id).isValid() ;
  bool       is_valid          = does_file_exist  && is_valid_length   &&
                                 !is_id_collision && !is_duplicate_clip ;

DEBUG_TRACE_CREATE_CLIP

  if (!is_valid)
  {
    if (is_id_collision) AudioTagToo::Warning(GUI::ID_COLLISION_ERROR_MSG) ;

    return ValueTree::invalid ;
  }

  // prepare metadata presentation
  master_node                 = (is_new_master) ? ValueTree(master_id) : master_node ;
  ValueTree clip_node         = ValueTree(clip_id) ;
  String    master_label_text = File(audio_filename).getFileName() ;
  String    clip_label_text   = AudioTagToo::DurationString(begin_time           ) + " - " +
                                AudioTagToo::DurationString(end_time             ) ;
  String    duration          = AudioTagToo::DurationString(end_time - begin_time) ;

  // configure and store new clip
  setProperty(clip_node , STORE::LABEL_TEXT_KEY , clip_label_text) ;
  setProperty(clip_node , STORE::FILENAME_KEY   , audio_filename ) ;
  setProperty(clip_node , STORE::BEGIN_TIME_KEY , begin_time     ) ;
  setProperty(clip_node , STORE::END_TIME_KEY   , end_time       ) ;
  setProperty(clip_node , STORE::DURATION_KEY   , duration       ) ;
  master_node.appendChild(clip_node , nullptr) ;

  // configure and store new master
  if (is_new_master)
  {
    setProperty(master_node , STORE::LABEL_TEXT_KEY , master_label_text) ;
    setProperty(master_node , STORE::FILENAME_KEY   , audio_filename   ) ;
    this->clips.appendChild(master_node , nullptr) ;
  }

  // sort masters and clips
  STORE::IdComparator<ValueTree&> id_comparator ;
  this->clips.sort(id_comparator , nullptr , false) ;
  master_node.sort(id_comparator , nullptr , false) ;

DEBUG_TRACE_DUMP_STORE(master_node , "master_node")

  return clip_node ;
}


/* AudioTagTooStore private instance methods */

/* persistence */

void AudioTagTooStore::loadConfig()
{
// DEBUG_TRACE_LOAD_CONFIG

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

  // load audio file peaks cache from persistent storage
  FileInputStream* peaks = new FileInputStream(this->peaksCacheFile) ;
  if (peaks->openedOk()) this->thumbnailCache.readFromStream(*peaks) ;
  delete peaks ;
}

bool AudioTagTooStore::storeConfig(XmlElement* device_state_xml)
{
DEBUG_TRACE_STORE_CONFIG

  // prepare storage directory
  if (this->storageTempFile.create().failed() || !this->storageTempFile.deleteFile())
  {
    AudioTagToo::Error(GUI::FILESYSTEM_WRITE_ERROR_MSG) ;

    return false ;
  }

DEBUG_TRACE_DUMP_STORE(this->root , "root")

  if (this->root.isValid() && this->clips.isValid() && this->compilations.isValid())
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
      AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
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
      AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "application configuration") ;
      delete storage_xml ;

      return false ;
    }

#endif // STORAGE_IS_BINARY
  }

  // marshall audio device configuration out to persistent XML storage
  if (device_state_xml != nullptr)
  {
    this->deviceStateXml.reset(device_state_xml) ;
    if (this->deviceStateXml->writeToFile(this->storageTempFile , String::empty))
      this->storageTempFile.moveFileTo(this->deviceFile) ;
    else
    {
      AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "audio device configuration") ;

      return false ;
    }
  }

  // marshall audio file peaks cache out to persistent binary storage
  FileOutputStream* peaks_stream = new FileOutputStream(this->storageTempFile) ;
  if (!peaks_stream->failedToOpen())
  {
    this->thumbnailCache.writeToStream(*peaks_stream) ;
    peaks_stream->flush() ;
    this->storageTempFile.moveFileTo(this->peaksCacheFile) ;
    delete peaks_stream ;
  }
  else
  {
    AudioTagToo::Error(GUI::STORAGE_WRITE_ERROR_MSG + "audio file peaks cache") ;
    delete peaks_stream ;

    return false ;
  }

  return true ;
}


/* validations */

void AudioTagTooStore::verifyConfig()
{
  // verify stored configuration or reset from defaults
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
  filterRogueKeys (this->root , STORE::RootPersistentKeys ) ;
  filterRogueNodes(this->root , STORE::RootPersistentNodes) ;
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
  NamedValueSet root_node_ids      = STORE::RootPersistentNodes ;
  int           n_duplicated_nodes = 0 ;
  bool          has_duplicates     = false ;

  n_duplicated_nodes = nDuplicatedNodes(stored_config , root_node_ids) ;
  has_duplicates     = has_duplicates || n_duplicated_nodes > root_node_ids.size() ;

  return has_duplicates ;
}

int AudioTagTooStore::nDuplicatedNodes(ValueTree parent_node , NamedValueSet node_ids)
{
  int n_duplicated_nodes = 0 ;

  for (int node_id_n = 0 ; node_id_n < node_ids.size() ; ++node_id_n)
  {
    Identifier node_id = STORE::FilterId(STRING(node_ids.getName(node_id_n))) ;

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

void AudioTagTooStore::filterRogueKeys(ValueTree parent_node , NamedValueSet persistent_keys)
{
  for (int key_n = 0 ; key_n < parent_node.getNumProperties() ; ++key_n)
  {
    Identifier property_id = parent_node.getPropertyName(key_n) ;

DEBUG_TRACE_FILTER_ROGUE_KEY

    if (!persistent_keys.contains(property_id))
      parent_node.removeProperty( property_id , nullptr) ;
  }
}

void AudioTagTooStore::filterRogueNodes(ValueTree parent_node , NamedValueSet persistent_node_ids)
{
  Identifier parent_id = parent_node.getType() ;

  for (int child_n = 0 ; child_n < parent_node.getNumChildren() ; ++child_n)
  {
    Identifier node_id = parent_node.getChild(child_n).getType() ;

DEBUG_TRACE_FILTER_ROGUE_NODE

    if (!persistent_node_ids.contains(node_id) || node_id == parent_id)
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


/* event handlers */

void AudioTagTooStore::listen(bool should_listen)
{
  if (!AudioTagToo::IsInitialized) return ;

DEBUG_TRACE_LISTEN

  if (should_listen) { this->root.addListener   (this) ; }
  else               { this->root.removeListener(this) ; }
}

void AudioTagTooStore::changeListenerCallback(ChangeBroadcaster* source)
{
  if (source == &(AudioTagToo::Gui->deviceManager))
  {
    bool        is_device_ready  = AudioTagToo::Gui->deviceManager.getCurrentAudioDevice() != nullptr ;
    XmlElement* device_state_xml = AudioTagToo::Gui->deviceManager.createStateXml() ;

DEBUG_TRACE_DEVICE_STATE_CHANGED

    if      (!is_device_ready           ) AudioTagToo::Warning(GUI::DEVICE_ERROR_MSG) ;
    else if (device_state_xml != nullptr) storeConfig(device_state_xml) ;
  }
}

void AudioTagTooStore::valueTreePropertyChanged(ValueTree& node , const Identifier& key)
{
DEBUG_TRACE_CONFIG_TREE_CHANGED

  if (isConfigProperty(node , key)) AudioTagToo::HandleConfigChanged(key) ;
}


/* helpers */

bool AudioTagTooStore::isConfigProperty(ValueTree node , const Identifier& key)
{
  Identifier  node_id       = node.getType() ;
  var         key_var       = var(STRING(key)) ;
  var         keys_var      = STORE::RootNodes[node_id] ;
  Array<var>* keys_array    = keys_var.getArray() ;
  bool        is_config_key = node.isValid()                                        &&
                              keys_array != nullptr && keys_array->contains(key_var) ;

  return is_config_key ;
}
