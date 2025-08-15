<a href="https://shogun.ms" target="_blank" rel="noopener">
  <img src="https://cdn.shogun.ms/assets/shogun/Shogun_Icon_Small.png" alt="Shogun Icon" height="48"/>
</a>

---

# BudgetTracker
BudgetTracker is a lightweight, menu-driven terminal application for managing personal finances. It helps you record and maintain transactions, keep your data tidy, and get a clear picture of your spending and income over time.

This project was originally created as a way to learn and explore the C programming language.

# 🧩 Installation
1. Download the [latest](https://github.com/Almighty-Shogun/BudgetTracker/releases/latest) release.
2. Download the `BudgetTracker-OS-X-Y-Z.zip` file.
   1. For Windows and Ubuntu only.
3. Extract the archive.
4. Run the `BudgetTracker.exe` file.

> [!NOTE]
> The menu should be self-explanatory and each option has a help option to explain what it does.

# ⚠️ Requirements
- C23
- CMake version 3.31 or higher.
- [vcpkg](https://github.com/microsoft/vcpkg)
- [cJSON](https://github.com/DaveGamble/cJSON) (installed using vcpkg)

# 🛠️ Building
For building please see the requirements above.

## Make
This is the preferred way of building the project on Linux environments. 
```shell
git clone https://github.com/Almighty-Shogun/BudgetTracker.git
cd BudgetTracker
make
```

## CMake
CMake enables the user to build the project on any other environment other than Linux. It also allows the use of an IDE to build the project automatically.
```shell
git clone https://github.com/Almighty-Shogun/BudgetTracker.git
cd BudgetTracker
mkdir build && cd build
cmake ..
make
```

## Using an IDE
If you are using an IDE like Visual Studio or CLion, you can open the project and build it using the **Run/Debug configurations**.

# 📦 Semantic Versioning (SemVer)
This project follows Semantic Versioning (SemVer), which uses a version format of `MAJOR.MINOR.PATCH`.

- **Patch** — Increases when backward-compatible bug fixes are made. These are small changes that address incorrect behavior without adding new features or functionality.
- **Minor** — Increases when new features or functionality are added in a backward-compatible manner. This includes adding new methods, classes, or capabilities that do not break existing code.
- **Major** — Increases when breaking changes are introduced that are not backward-compatible, such as modifying method signatures, removing functionality, or changing existing behavior in a way that may break dependent code.

