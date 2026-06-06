# Swisstrain V1 Scope and Authoring Mode Specification

## Overview
This document defines the scope and authoring approach for Swisstrain V1, an editor-first Swiss landscape and rail sandbox.

## Key Decisions

### 1. Unreal Engine Version
- **Unreal Engine 5.5** - Latest version with enhanced landscape and rail tools
- Provides access to newest features and optimizations
- Strong support for large open worlds and editor performance

### 2. Authoring Mode
- **Editor-First Tooling** - Primary development happens in Unreal Editor
- Focus on editor experience with runtime as optional enhancement
- All core systems should be editable and previewable without compilation

### 3. Target Platforms
- **Primary**: Windows 10/11 (64-bit)
- **Future**: Linux and macOS (support in later versions)

### 4. Asset Policy
- **Pragmatic Assets** - Mix of procedural generation and custom assets
- Use of real-world Swiss landscape data where available
- Efficient asset streaming for large landscapes
- **LFS Integration**: Git LFS for large binary assets (textures, meshes, heightmaps)

### 5. Terrain Fidelity
- **Hybrid approach**: swisstopo 1:1 base with artistic cleaning
- **Base layer**: Accurate elevation data from Swiss topo surveys
- **Detail layer**: Artistically enhanced for visual appeal
- **LOD System**: Automatic LOD based on distance and importance

### 6. V1 Rail Types
- **Standard Gauge Only**: Focus on normal railway (1435mm) for V1
- Future versions will include narrow gauge and mountain railways

### 7. Blueprint/C++ Mix
- **Blueprint-first** approach with targeted C++ where needed
- UI, editor tools, and gameplay logic in Blueprints
- Performance-critical systems and base classes in C++
- Hybrid Approach:
  - Landscape/Rail systems: C++ base with Blueprint customization layers
  - Editor tools: Blueprint with C++ utility functions
  - Simulation systems: C++ core with Blueprint configuration interfaces

### 8. Repository and Build Conventions
- **Git Workflow**: Feature branch with pull request model
- **LFS Management**: 
  - Textures (.png, .jpg, .tga) in LFS
  - Meshes (.fbx) in LFS
  - Heightmaps and large data files in LFS
- **Directory Structure**:
  ```
  /Content
    /Landscape  - Terrain and environment assets
    /Rail       - Railway system assets and blueprints
    /UI         - User interface elements
    /Plugins    - Custom plugin modules
    /Maps       - Level files
  /Source       - C++ source files
  /Docs         - Documentation
  /Scripts      - Build and utility scripts
  ```
- **Build System**: Standard Unreal build process with custom automation scripts
- **CI/CD**: Automated builds on push to main branches
- **Minimal Build Scaffold**: Start with minimal viable build infrastructure and expand as needed

## V1 Deliverables

### Core Systems
1. **Landscape System**
   - Terrain generation from real data
   - Sculpting tools for artistic enhancement
   - Texturing and material system

2. **Rail System**
   - Track placement and editing system
   - Standard gauge support
   - Basic train physics

3. **Editor Tools**
   - Landscape sculpting interface
   - Rail placement tools
   - Asset management UI

4. **Simulation Framework**
   - Basic train movement
   - Simple scheduling system
   - Camera and navigation controls

### Technical Requirements
- Support for landscapes up to 100km²
- Up to 100km of railway tracks per map
- Support for 50+ train assets with basic AI
- 60 FPS on mid-range hardware (RTX 3070, Ryzen 5 5600X)

### Documentation
- Developer setup guide
- Editor tool usage documentation
- Plugin development guidelines
- Asset creation workflows

## Next Steps
This specification provides the foundation for implementation. Downstream workers should use this document as the basis for their specialized tasks in landscape, rail, editor tools, and simulation systems.