# Swisstrain Developer Setup Guide

## Prerequisites

- Unreal Engine 5.5
- Git with Git LFS
- Windows 10/11 (64-bit)
- Python 3.7+ with numpy and scipy (for data processing scripts)

## Setup Instructions

1. Clone the repository:
```
git clone <repository-url>
cd swisstrain
```

2. Install Git LFS:
```
git lfs install
git lfs pull
```

3. Set up Python dependencies for data processing:
```
pip install numpy scipy
```

4. Set up Unreal Engine 5.5:
- Download and install Unreal Engine 5.5 from Epic Games Launcher
- Launch the editor and open the Swisstrain project

5. Verify data processing scripts:
```
python Scripts/process_swisstopo_data.py --help
python Scripts/validate_swisstopo_data.py --help
```

## Directory Structure

```
/Content
  /Landscape  - Terrain and environment assets
    /Heightmaps - Processed terrain data
    /Materials  - Landscape materials
    /Textures   - Landscape textures
    /Water      - Water system assets
    /Foliage    - Vegetation assets
  /Rail       - Railway system assets and blueprints
  /UI         - User interface elements
  /Plugins    - Custom plugin modules
  /Maps       - Level files
/Source       - C++ source files
  /SwisstrainLandscape - Landscape system module
  /SwisstrainRail      - Rail system module
/Docs         - Documentation
/Scripts      - Build and utility scripts
```

## Git Workflow

- Feature branch model with pull requests
- Git LFS for large binary assets (textures, meshes, heightmaps)
- Follow Unreal Engine best practices for asset management
- Keep documentation in sync with code changes

## Data Processing Workflow

For terrain development:

1. Acquire swisstopo DHM data for the bounding box:
   - Top-left: 2673957.58, 1216900.00 (EPSG:2056)
   - Bottom-right: 2689486.72, 1204462.45 (EPSG:2056)

2. Process the data using the provided scripts:
```
python Scripts/process_swisstopo_data.py <input_file> Content/Landscape/Heightmaps/
```

3. Validate the processed data:
```
python Scripts/validate_swisstopo_data.py Content/Landscape/Heightmaps/<processed_file>.raw --type raw
```

4. Import into Unreal Engine using the import runbook (docs/import-runbook.md)

## Build Process

1. Run the build script in Scripts/Build/build.sh
2. The build script will compile C++ modules and package assets
3. Output will be placed in the /Binaries directory

## Documentation Guidelines

All major workflows should be documented:
- Data processing steps
- Unreal Engine import procedures
- System configuration guides
- Troubleshooting procedures

Refer to docs/ for comprehensive documentation on each system.

## Common Issues

- If Git LFS files are not properly pulled, run `git lfs pull`
- If the project fails to load in Unreal Engine, verify Unreal Engine 5.5 is installed
- For build issues, check the console output and Unreal Engine logs
- For data processing script issues, ensure numpy and scipy are installed

## Contributing

1. Create a feature branch from main
2. Make your changes
3. Update relevant documentation
4. Ensure all tests pass
5. Submit a pull request for review