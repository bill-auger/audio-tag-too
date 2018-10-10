
#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


/**
  JuceBoilerplateStore is the model class for the JuceBoilerplate application.
  It holds the runtime configuration via shared value holders
      and handles persistence via XML or JUCE binary storage.
*/
class JuceBoilerplateStore : ValueTree::Listener
{
  friend class MainContent ;


public:

  ~JuceBoilerplateStore() ;


private:

  // initialization
  JuceBoilerplateStore() ;
  bool initialize() ;
  void teardown() ;

  // validations
  void verifyConfig() ;
  void verifyRoot  () ;
  void sanitizeRoot() ;

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
  void loadConfig () ;
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
  bool isKnownProperty(ValueTree node        , const Identifier& key) ;
  void setProperty    (ValueTree node        , const Identifier& key , const var value) ;
  bool setConfig      (ValueTree config_node , const Identifier& key , const var value) ;

  // configuration/persistence
  File                        storageFile ;
  File                        storageXmlFile ;
  File                        deviceXmlFile ;
  ValueTree                   root ;           // persistent static config (STORE::STORAGE_ID node)
  std::unique_ptr<XmlElement> deviceStateXml ; // Juce AudioDeviceManager state
} ;
