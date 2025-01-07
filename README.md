# Camellia

Camellia is a general-purpose programming language characterized by:

- **Interfacial Design**: Emphasizing modular and extensible interfaces.
- **Lightweight**: Minimal resource usage.
- **High Versatility**: Broad applicability across domains.
- **Zero Platform Dependency**: Designed to work without platform-specific dependencies.

Camellia can be executed either via interpretation or compilation, providing developers with flexibility depending on their needs.

## Table of Contents

1. [Introduction](#introduction)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Contributing](#contributing)
5. [License](#license)
6. [Development Roadmap](#development-roadmap)

## Introduction

Camellia is under active development using C++ and CMake. The language aims to empower developers with a robust, portable, and adaptable tool for diverse programming scenarios. The project is hosted at:

[Camellia on GitHub](https://github.com/saisesai/camellia)

## Installation

As Camellia is still in development, it must be built from source. Follow these steps to set up Camellia:

1. Clone the repository:
   ```bash
   git clone https://github.com/saisesai/camellia.git
   ```
2. Build the project using CMake:
   ```bash
   cd camellia/camellia/cc
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the resulting executable to begin using Camellia.

## Usage

Detailed usage instructions will be provided in future releases. For now, build the project and explore its features as they are developed.

## Contributing

Contributions to Camellia are welcome! Follow these steps to get involved:

1. Fork this repository.
2. Create your feature branch:
   ```bash
   git checkout -b feature/your-feature
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add some feature"
   ```
4. Push to the branch:
   ```bash
   git push origin feature/your-feature
   ```
5. Submit a Pull Request.

## License

Camellia is licensed under BSD 3-Clause License:

```
BSD 3-Clause License

Copyright (c) 2024, camellia development team
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```

## Development Roadmap

### 0.0.x Phase
- Implement a compiler from `lia` to `C` using C++.

### 0.1.x Phase
- Achieve self-hosting capabilities.

### 0.2.x Phase
- Develop an interpreter for the language.

### 0.3.x Phase
- Implement machine code generation and Just-In-Time (JIT) compilation.

Additional information (optional): Include contact details, acknowledgments, or plans for future development.

