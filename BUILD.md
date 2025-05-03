## 🚀 Pre-built Releases (Recommended)

We also automatically build and upload pre-compiled installers via **GitHub Actions**:

- ✅ **Windows Installer** (.exe)  
- ✅ **Linux AppImage** (.AppImage)

You can download them directly from the [Releases](https://github.com/xaprier/XFakeContrib/releases) section.  
This is the easiest and fastest way to use **XFakeContrib** without building manually.

> **Note:** The Release assets are built automatically on each version/tag push to the repository.

---

## 🛠️ Build Instructions

Follow these steps to build **XFakeContrib** from source.

---

### 📚 Prerequisites

Make sure the following are installed:

- **CMake** (version 3.15 or later)
- **GCC** or **Clang** (C++17 compatible compiler)
- **Qt 5.15.2+** (Core, Widgets, Network, Svg, Concurrent modules)
- **Git** (for submodules and Git commands)

---

## 🐧 Linux Build Instructions

1. **Install required packages:**

   On Ubuntu / Debian-based systems:

   ```bash
   sudo apt update
   sudo apt install build-essential cmake qt5-default qtbase5-dev qt5-svg-dev libqt5concurrent5 git libgmock-dev libgtest-dev qtbase5-dev libqt5svg5-dev qttools5-dev
   ```

2. **Clone the repository with submodules:**

   ```bash
   git clone --recurse-submodules https://github.com/xaprier/XFakeContrib.git
   cd XFakeContrib
   ```

3. **Create a build directory:**

   ```bash
   mkdir build
   cd build
   ```

4. **Configure the project:**

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
   ```

5. **Build the project:**

   ```bash
   cmake --build . --config Release
   ```

6. **Run the application:**

   ```bash
   ./XFakeContrib
   ```

7. **Install to the system if you want:**
   ```bash
   sudo cmake --install .
   ```

---

## 🪟 Windows Build Instructions (MinGW)

You have two options to build on Windows (MinGW):

- If you **only want the application**, follow the basic build steps.
- If you **want to create an installer (.exe)**, follow the installer build steps.

---

<details>
<summary><b>🚀 Build without Installer</b></summary>

1. **Clone the repository with submodules:**

   ```bash
   git clone --recurse-submodules https://github.com/xaprier/XFakeContrib.git
   cd XFakeContrib
   ```

2. **Create a build directory:**

   ```bash
   mkdir build
   cd build
   ```

3. **Configure the project:**

   ```bash
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

4. **Build the project:**

   ```bash
   cmake --build . --config Release
   ```

5. **Run the application:**

   Inside the `Release` folder:

   ```bash
   ./XFakeContrib.exe
   ```

</details>

---

<details>
<summary><b>📦 Build with Installer (Inno Setup)</b></summary>

1. **Get [Inno Setup](https://jrsoftware.org/isdl.php)** if you don't have it installed.

2. **Clone the repository with submodules:**

   ```bash
   git clone --recurse-submodules https://github.com/xaprier/XFakeContrib.git
   cd XFakeContrib
   ```

3. **Run the deploy.ps1 under project path:**

   ```bash
   .\deploy.ps1
   ```

4. **Installer will be ready:**

  x64 is your CPU architecture and it can be changed.
   ```bash
   cd build/install/Output/
   ./XFakeContrib-x64-installer.exe
   ```

</details>

---

### 📢 Note:

- The **installer build** is optional.  
- If you just want to run the app, you don't need Inno Setup.
- A prebuilt Windows Installer is also available under the [Releases](https://github.com/xaprier/XFakeContrib/releases) page.
