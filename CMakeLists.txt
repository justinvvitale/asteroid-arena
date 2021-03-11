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
        src/main.cpp src/core/input/KeyRegistry.cpp src/core/input/KeyRegistry.h src/core/ecs/Entity.cpp src/core/ecs/Entity.h src/core/shared/engine_math.h src/core/ecs/Component.cpp src/core/ecs/Component.h src/core/ecs/components/MeshComponent.cpp src/core/ecs/components/MeshComponent.h src/core/Engine.cpp src/core/Engine.h src/core/Game.cpp src/core/Game.h src/core/Scene.cpp src/core/Scene.h src/core/ecs/components/ScriptComponent.cpp src/core/ecs/components/ScriptComponent.h src/core/ecs/System.h src/core/ecs/systems/MeshRendererSystem.cpp src/core/ecs/systems/MeshRendererSystem.h)
