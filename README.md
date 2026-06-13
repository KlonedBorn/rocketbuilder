# Rocket Builder

Rocket Builder is a sandbox physics game designed for engineering hobbyists who enjoy games like **The Powder Toy**, **Space Simulator Toolkit**, and **Poly Bridge**. 

Inspired by Crypticsea's prototype "rocketbuilder," this game challenges players to sketch and draw their rockets to optimize performance. Your goal is to extract as much delta-V or velocity as possible from the expansion of simulated gas particles produced by the burning of propellant particles.

## Getting Started

### Prerequisites

To build this project, you will need the following tools:

- **vcpkg**: For managing dependencies.
- **CMake** (version 4.3.2 or higher): Build system.
- **W64devkit**: Highly recommended for a successful build environment on Windows.

### Dependencies

Rocket Builder uses the following libraries:

- **SFML** (version 3.0.1)
- **Dear ImGui** (version 1.91.9)
- **ImGui-SFML**: Backend for SFML (compatible with Dear ImGui 1.91.x).
- **Box2D**: Physics engine.

## Building

This project uses **CMake Presets** and **vcpkg** with the `x64-mingw-static` triplet to ensure a consistent build environment with W64devkit.

1. Clone the repository.
2. Ensure `vcpkg` is installed and the path in `CMakePresets.json` matches your local setup.
3. Configure and build using CMake Presets:
   ```bash
   # For Debug build
   cmake --preset debug
   cmake --build --preset debug

   # For Release build
   cmake --preset release
   cmake --build --preset release
   ```

Note: The build system automatically copies the `assets/` directory to the output folder so relative paths work correctly during execution.

## License

This project is licensed under the **GNU General Public License v3.0**. See the `LICENSE` file for details.
