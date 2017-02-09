#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

void parseResources(
     TiXmlElement*                 pScene,
     Ogre::ResourceGroupManager   &pRgm,
     Ogre::Log                    *pLogger
){
     char *buffer = new char[2056];

     //Get the resource group name
     const char* sceneName = pScene->Attribute("name");
     if (sceneName == NULL) {
          // HANDLE ERROR
          pLogger->logMessage("No scene name set, using Default-Scene!");
          sceneName = "Default-Scene";
     }

     //Parse paths
     pLogger->logMessage("Parsing paths...");
     int pathCount = 0;
     for (TiXmlElement* paths = pScene->FirstChildElement("paths");
          paths != NULL;
          paths = paths->NextSiblingElement("paths"))
     {
          for (TiXmlElement* path = paths->FirstChildElement("path");
               path != NULL;
               path = path->NextSiblingElement("path"))
          {
               pRgm.addResourceLocation(path->GetText(), "FileSystem", sceneName);
               pathCount++;
          }
     }
     sprintf(buffer, "Parsed %d path(s).", pathCount);
     pLogger->logMessage(buffer);

     //Parse models
     pLogger->logMessage("Parsing models...");
     int modelCount = 0;
     for (TiXmlElement* models = pScene->FirstChildElement("models");
          models != NULL;
          models = models->NextSiblingElement("models"))
     {
          for (TiXmlElement* model = models->FirstChildElement("model");
               model != NULL;
               model = model->NextSiblingElement("model"))
          {
               pRgm.declareResource(model->GetText(), "Mesh", sceneName);
               modelCount++;
          }
     }
     sprintf(buffer, "Parsed %d model(s).", modelCount);
     pLogger->logMessage(buffer);

     pRgm.initialiseResourceGroup(sceneName);
	pRgm.loadResourceGroup(sceneName, true, true);

     delete[] buffer;
}

void parseNode(
     TiXmlElement       *pNode,
     Ogre::SceneNode    *pParent,
     Ogre::SceneManager *pSceneManager,
     Ogre::Log          *pLogger
){

     //Create the Ogre::SceneNode
     Ogre::SceneNode* _Node;
     const char* nodeName = pNode->Attribute("name");
     if (nodeName != NULL) {
          _Node = pParent->createChildSceneNode(nodeName);
     }
     else {
          _Node = pParent->createChildSceneNode();
     }

     //Parse entities
     pLogger->logMessage("Parsing entities...");
     for (TiXmlElement* entity = pNode->FirstChildElement("entity");
          entity != NULL;
          entity = entity->NextSiblingElement("entity"))
     {
          const char* meshName = entity->GetText();
          if (meshName != NULL) {
               Ogre::Entity* _Entity = pSceneManager->createEntity(meshName);
               const char* materialName = entity->Attribute("material");
               if (materialName != NULL) {
                    _Entity->setMaterialName(materialName);
               }
               _Node->attachObject(_Entity);
          }
     }
     pLogger->logMessage("Entities parsed.");

     //Parse translations
     pLogger->logMessage("Parsing translations...");
     for (TiXmlElement* translation = pNode->FirstChildElement("translate");
          translation;
          translation = translation->NextSiblingElement("translate"))
     {
          float x = 0, y = 0, z = 0;
          translation->QueryFloatAttribute("x", &x);
          translation->QueryFloatAttribute("y", &y);
          translation->QueryFloatAttribute("z", &z);
          _Node->translate(Ogre::Vector3(x, y, z));
     }
     pLogger->logMessage("Translations parsed.");

     //Parse rotations
     pLogger->logMessage("Parsing rotations...");
     for (TiXmlElement* rotation = pNode->FirstChildElement("rotate");
          rotation != NULL;
          rotation = rotation->NextSiblingElement("rotate"))
     {
          float a = 0, x = 0, y = 0, z = 0;
          rotation->QueryFloatAttribute("a", &a);
          rotation->QueryFloatAttribute("x", &x);
          rotation->QueryFloatAttribute("y", &y);
          rotation->QueryFloatAttribute("z", &z);
          _Node->rotate(Ogre::Quaternion(Ogre::Degree(a), Ogre::Vector3(x, y, z)));
     }
     pLogger->logMessage("Rotations parsed.");

     //Parse children
     pLogger->logMessage("Parsing children...");
     for (TiXmlElement* child = pNode->FirstChildElement("node");
          child != NULL;
          child = child->NextSiblingElement("node"))
     {
          parseNode(child, _Node, pSceneManager, pLogger);
     }
     pLogger->logMessage("Children parsed.");
}

bool parseScene (
     const char*                   pFileName,
     Ogre::SceneManager*           pSceneManager,
     Ogre::ResourceGroupManager   &pRgm,
     Ogre::Log                    *pLogger
){
     char* buffer = new char[2056];

     TiXmlDocument doc(pFileName);
     if (!doc.LoadFile()) {
          // HANDLE ERROR
          pLogger->logMessage("Failed to load XML document!");
          return false;
     }

     TiXmlElement* scene = doc.RootElement();

     //Parse resources
     pLogger->logMessage("Parsing resources...");
     parseResources(scene, pRgm, pLogger);
     pLogger->logMessage("Resources parsed.");

     //Parse scene nodes
     pLogger->logMessage("Parsing nodes...");
     int nodeCount = 0;
     for (TiXmlElement* node = scene->FirstChildElement("node");
          node != NULL;
          node = node->NextSiblingElement("node"))
     {
          parseNode(node, pSceneManager->getRootSceneNode(), pSceneManager, pLogger);
          nodeCount++;
     }
     pLogger->logMessage("Nodes parsed.");

     delete [] buffer;
     return true;
}

#endif
