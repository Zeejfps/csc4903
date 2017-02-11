#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

Ogre::Vector3 parseVector3(TiXmlElement* node){
     float x=0, y=0, z=0;
     node->QueryFloatAttribute("x", &x);
     node->QueryFloatAttribute("y", &y);
     node->QueryFloatAttribute("z", &z);
     return Ogre::Vector3(x, y, z);
}

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
     TiXmlElement* paths = pScene->FirstChildElement("paths");
     if (paths != NULL) {
          pLogger->logMessage("Parsing paths...");
          int pathCount = 0;
          for (TiXmlElement* path = paths->FirstChildElement("path");
               path != NULL;
               path = path->NextSiblingElement("path"))
          {
               pRgm.addResourceLocation(path->GetText(), "FileSystem", sceneName);
               pathCount++;
          }
          sprintf(buffer, "Parsed %d path(s).", pathCount);
          pLogger->logMessage(buffer);
     }

     //Parse models
     TiXmlElement* models = pScene->FirstChildElement("models");
     if (models != NULL) {
          pLogger->logMessage("Parsing models...");
          int modelCount = 0;
          for (TiXmlElement* model = models->FirstChildElement("model");
               model != NULL;
               model = model->NextSiblingElement("model"))
          {
               pRgm.declareResource(model->GetText(), "Mesh", sceneName);
               modelCount++;
          }
          sprintf(buffer, "Parsed %d model(s).", modelCount);
          pLogger->logMessage(buffer);
     }

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
          const char* entityName = entity->Attribute("name");
          const char* meshFile = entity->Attribute("meshFile");
          if (meshFile != NULL) {
               Ogre::Entity* _Entity;
               if (entityName != NULL) {
                    _Entity = pSceneManager->createEntity(entityName, meshFile);
               }
               else {
                    _Entity = pSceneManager->createEntity(meshFile);
               }
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
          Ogre::Vector3 vec = parseVector3(translation);
          _Node->translate(vec);
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

     //Parse cameras
     TiXmlElement* cameras = scene->FirstChildElement("cameras");
     if (cameras != NULL) {
          pLogger->logMessage("Parsing cameras...");
          for (TiXmlElement* camera = cameras->FirstChildElement("camera");
               camera != NULL;
               camera = camera->NextSiblingElement("camera"))
          {
               Ogre::Camera* _Camera;
               const char* cameraName = camera->Attribute("name");
               if (cameraName != NULL) {
                    _Camera = pSceneManager->createCamera(cameraName);
               }
               else {
                    // ERROR CAMERA MUST HAVE A NAME
                    pLogger->logMessage("No camera name given! Failed to create camera!");
                    continue;
               }
               TiXmlElement* position = camera->FirstChildElement("position");
               if (position != NULL) {
                    Ogre::Vector3 vec = parseVector3(position);
                    _Camera->setPosition(vec);
               }
               TiXmlElement* lookAt = camera->FirstChildElement("lookAt");
               if (lookAt != NULL) {
                    Ogre::Vector3 vec = parseVector3(lookAt);
                    _Camera->lookAt(vec);
               }
          }
          pLogger->logMessage("Cameras parsed");
     }

     //Parse lights
     TiXmlElement* lights = scene->FirstChildElement("lights");
     if (lights != NULL) {
          pLogger->logMessage("Parsing lights...");
          for (TiXmlElement* light = lights->FirstChildElement("light");
               light != NULL;
               light = light->NextSiblingElement("light"))
          {
               Ogre::Light* _Light;
               const char* lightName = light->Attribute("name");
               if (lightName != NULL) {
                    _Light = pSceneManager->createLight(lightName);
               }
               else {
                    _Light = pSceneManager->createLight();
               }
               TiXmlElement* position = light->FirstChildElement("position");
               if (position != NULL) {
                    Ogre::Vector3 vec = parseVector3(position);
                    _Light->setPosition(vec);
               }
          }
          pLogger->logMessage("Lights parsed");
     }

     //Parse scene nodes
     TiXmlElement* nodes = scene->FirstChildElement("nodes");
     if (nodes != NULL) {
          pLogger->logMessage("Parsing nodes...");
          for (TiXmlElement* node = nodes->FirstChildElement("node");
               node != NULL;
               node = node->NextSiblingElement("nodes"))
          {
               parseNode(node, pSceneManager->getRootSceneNode(), pSceneManager, pLogger);
          }
          pLogger->logMessage("Nodes parsed.");
     }

     delete [] buffer;
     return true;
}

#endif
