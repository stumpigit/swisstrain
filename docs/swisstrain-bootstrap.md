# Swisstrain Project Bootstrap

## Overview
Swisstrain is an editor-first Swiss landscape and rail sandbox simulation. The project aims to create a realistic yet artistically enhanced simulation of Swiss mountain landscapes with functional railway systems using Unreal Engine 5.5.

## Project Goals
- Create an immersive Swiss mountain landscape environment with stylized-realistic cozy visuals
- Implement realistic railway systems that can be edited and customized
- Provide an intuitive editor interface for landscape and rail development
- Support both swisstopo 1:1 accurate representations and artistically cleaned terrains
- Enable users to design, build, and simulate railway networks

## V1 Scope Considerations

### Technology Stack
- **Engine**: Unreal Engine 5.5
- **Primary Language**: Blueprint-first with targeted C++ extensions
- **Platforms**: PC (Windows 10/11 64-bit)
- **Version Control**: Git with LFS for asset management

### Core Features
1. Swiss landscape rendering with mountain terrain
2. Railway track placement and editing system (standard gauge only for V1)
3. Basic train simulation mechanics
4. Editor tools for landscape sculpting
5. Asset management system
6. Basic lighting and weather systems

### Asset Policy
- Pragmatic mix of procedural and custom assets
- Use of real-world Swiss landscape data where available
- Implementation of artistic enhancement options
- Efficient asset streaming for large landscapes
- Git LFS integration for large binary assets

### Development Approach
- Editor-first development for content creation
- Modular system design for extensibility
- Clear separation of editor vs. runtime tooling (with runtime as optional enhancement)
- Comprehensive documentation and examples