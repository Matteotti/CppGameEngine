#pragma once

#define ENGINE_WINDOW_TITLE "Engine Window"
#define ENGINE_WINDOW_WIDTH 800
#define ENGINE_WINDOW_HEIGHT 800

#define ENGINE_OPENGL_CONTEXT_VER_MAJOR 4
#define ENGINE_OPENGL_CONTEXT_VER_MINOR 6

#define ENGINE_ASSET_META_PATH "assets/META.yml"
#define ENGINE_ASSET_MESH_PATH "mesh"
#define ENGINE_ASSET_SHADER_PATH "shader"
#define ENGINE_ASSET_TEXTURE_PATH "texture"
#define ENGINE_LOG_PATH "./engine_log.txt"

// Note：优先级数字越小，则越先被 Update。
#define ENGINE_PRIORITY_COLLISION_SYSTEM 0
#define ENGINE_PRIORITY_PHYSICS_SYSTEM 1
#define ENGINE_PRIORITY_TRANSLATE_SYSTEM 2
#define ENGINE_PRIORITY_CAMERA_SYSTEM 3
#define ENGINE_PRIORITY_RENDER_SYSTEM 4
#define ENGINE_PRIORITY_WINDOW_SYSTEM 5
#define ENGINE_PRIORITY_RESOURCE_SYSTEM 5
