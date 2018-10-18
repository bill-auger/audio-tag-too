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


#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


/**
  AudioTagTooStore is the model class for the AudioTagToo application.
  It holds the runtime configuration via shared value holders
      and handles persistence via XML or JUCE binary storage.
*/
class AudioTagTooStore : ValueTree::Listener
{
  friend class MainContent ;


public:

  ~AudioTagTooStore(void) ;


private:

  // initialization
  AudioTagTooStore(void) ;
  bool initialize(void) ;
  void teardown(void) ;

  // validations
  void verifyConfig(void) ;
  void verifyRoot  (void) ;
  void sanitizeRoot(void) ;

  // validation/sanitization helpers
  void verifyChildNode      (ValueTree store , Identifier node_id) ;
  void verifyRootChildNode  (Identifier node_id) ;
  void verifyProperty       (ValueTree store , Identifier key , var default_value) ;
  void verifyRootProperty   (Identifier key , var default_value) ;
  bool hasDuplicatedNodes   (ValueTree stored_config) ;
  int  nDuplicatedNodes     (ValueTree parent_node , StringArray node_ids) ;
  void removeConflictedNodes(ValueTree parent_node , Identifier node_id) ;
  void filterRogueKeys      (ValueTree parent_node , StringArray persistent_keys) ;
  void filterRogueNodes     (ValueTree parent_node , StringArray persistent_node_ids) ;
  void sanitizeIntProperty  (ValueTree store , Identifier key , int min_value , int max_value) ;
  void sanitizeComboProperty(ValueTree store , Identifier key , StringArray options) ;

  // persistence
  void loadConfig (void) ;
  bool storeConfig(XmlElement* device_state_xml) ;

  // event handlers
  void listen                  (bool should_listen) ;
  void valueTreePropertyChanged(ValueTree& node , const Identifier& key) override ;

  // unhandled ValueTree::Listener events
  void valueTreeChildAdded       (ValueTree& /*parent_node*/ , ValueTree& /*new_node*/                       ) override { }
  void valueTreeChildRemoved     (ValueTree& /*parent_node*/ , ValueTree& /*deleted_node*/ , int /*prev_idx*/) override { }
  void valueTreeChildOrderChanged(ValueTree& /*parent_node*/ , int        /*prev_idx*/     , int /*curr_idx*/) override { }
  void valueTreeParentChanged    (ValueTree& /*reparented_node*/                                             ) override { }
  void valueTreeRedirected       (ValueTree& /*target_node*/                                                 ) override { }

  // getters/setters
  bool      isKnownProperty (ValueTree node        , const Identifier& key) ;
  bool      setProperty     (ValueTree node        , const Identifier& key , const var value) ;
  bool      setConfig       (ValueTree config_node , const Identifier& key , const var value) ;
  ValueTree getChildNodeById(ValueTree root_store , Identifier node_id) ;
  bool      createClip      (String audio_filename , double begin_time , double end_time) ;

  // configuration/persistence
  File                        storageFile ;
  File                        storageXmlFile ;
  File                        deviceXmlFile ;
  ValueTree                   root ;           // persistent static config   (STORE::STORAGE_ID node)
  ValueTree                   clips ;          // persistent volatile config (STORE::CLIPS_ID node)
  ValueTree                   compilations ;   // persistent volatile config (STORE::COMPILATIONS_ID node)
  std::unique_ptr<XmlElement> deviceStateXml ; // Juce AudioDeviceManager state
} ;
