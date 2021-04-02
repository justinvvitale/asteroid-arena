cmake_minimum_required(VERSION 3.17)
project(I3D)

set(CMAKE_CXX_STANDARD 14)

include_directories(libs/include)
include_directories(libs/include/GL)
include_directories(libs/include/SOIL)

link_directories(libs/lib)


add_executable(I3D
        libs/include/GL/freeglut.h
        libs/include/GL/freeglut_ext.h
        libs/include/GL/freeglut_std.h
        libs/include/GL/glew.h
        libs/include/GL/glut.h
        libs/include/GL/glxew.h
        libs/include/GL/wglew.h
        libs/include/SOIL/SOIL.h
        src/A1/main.cpp src/core/input/KeyRegistry.cpp src/core/input/KeyRegistry.h src/core/ecs/Entity.cpp src/core/ecs/Entity.h src/core/shared/engine_math.h src/core/ecs/Component.cpp src/core/ecs/Component.h src/core/ecs/components/MeshComponent.cpp src/core/ecs/components/MeshComponent.h src/core/Engine.cpp src/core/Engine.h src/core/Game.cpp src/core/Game.h src/core/Scene.cpp src/core/Scene.h src/core/ecs/components/ScriptComponent.cpp src/core/ecs/components/ScriptComponent.h src/core/ecs/System.h src/core/ecs/systems/MeshRendererSystem.cpp src/core/ecs/systems/MeshRendererSystem.h src/core/shared/engine_graphic.h src/A1/entities/ArenaEntity.h src/A1/entities/ShipEntity.h src/core/ecs/systems/ScriptProcessorSystem.cpp src/core/ecs/systems/ScriptProcessorSystem.h src/core/ecs/enums/ComponentType.h src/A1/GAMECONFIG.h src/A1/scripts/PlayerControllerScript.cpp src/A1/scripts/PlayerControllerScript.h src/core/ecs/systems/CollisionSystem.cpp src/core/ecs/systems/CollisionSystem.h src/core/ecs/components/ColliderComponent.cpp src/core/ecs/components/ColliderComponent.h src/A1/entities/TestEntity.h src/core/ENGINECONFIG.h src/core/Renderer.cpp src/core/Renderer.h src/A1/scripts/WallScript.cpp src/A1/scripts/WallScript.h src/A1/entities/AsteroidEntity.h src/core/ecs/components/RigidbodyComponent.cpp src/core/ecs/components/RigidbodyComponent.h src/A1/scripts/AsteroidWaveScript.cpp src/A1/scripts/AsteroidWaveScript.h src/A1/scripts/AsteroidScript.cpp src/A1/scripts/AsteroidScript.h src/core/ecs/systems/ParticleSystem.cpp src/core/ecs/systems/ParticleSystem.h src/core/ecs/components/ParticleEmitterComponent.cpp src/core/ecs/components/ParticleEmitterComponent.h src/A1/entities/BulletEntity.h src/A1/scripts/ScoreScript.cpp src/A1/scripts/ScoreScript.h src/A1/entities/ScoreManagerEntity.h src/core/ecs/components/TextComponent.cpp src/core/ecs/components/TextComponent.h src/core/ecs/systems/TextRendererSystem.cpp src/core/ecs/systems/TextRendererSystem.h)
