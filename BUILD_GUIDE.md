# 构建脚本使用说明

本项目使用 Shell 脚本进行构建和管理，适用于 Git Bash、MSYS2、WSL 等 Unix-like 环境。

## Shell 脚本

### 快速构建和运行
```bash
# 构建项目
./build.sh

# 运行主程序（Qt GUI）
./build/bin/WindowsAPIApp.exe
```

### 手动步骤
如果脚本无法运行，可以手动执行以下命令：

```bash
# 1. 创建构建目录
mkdir -p build
cd build

# 2. 配置项目 (MinGW)
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release

# 3. 编译项目
cmake --build . --parallel

# 4. 返回根目录
cd ..

# 5. 运行测试
./build/bin/SmokeTest.exe
```


## 环境要求

- **MinGW**: 确保 MinGW 已添加到 PATH 环境变量
- **CMake**: 版本 3.16 或更高
- **Qt5**: Qt5 开发库 (推荐 5.15.2 或更高)
- **编译器**: GCC 支持 C++17

### 常见 MinGW 路径
- `C:\MinGW\bin`
- `C:\msys64\mingw64\bin`
- `D:\Qt\Tools\mingw1310_64\bin` (Qt 自带)

### 常见 Qt5 路径
- `C:\Qt\5.15.2\mingw81_64\bin`
- `D:\Qt\5.15.2\mingw81_64\bin`

## 构建输出

成功构建后，可执行文件将位于：
- **主程序**: `build/bin/WindowsAPIApp.exe`
- 测试程序: `build/bin/SmokeTest.exe`

## 故障排除

### 1. "gcc 未找到"
确保 MinGW 已正确安装并添加到 PATH 环境变量。

### 2. "cmake 未找到"
确保 CMake 已安装并添加到 PATH 环境变量。

### 3. 编译错误
检查源代码文件是否完整，依赖库是否正确链接。

### 4. 脚本无法执行
尝试手动执行脚本中的命令，或使用对应的 .bat 文件。

## 推荐工作流

1. **构建**: 使用 `./build.sh` 构建项目
2. **运行**: 直接运行 `./build/bin/WindowsAPIApp.exe`
3. **清理**: 使用 `./clean.sh` 清理构建文件

## 脚本说明

- **build.sh**: 构建整个项目，生成所有可执行文件
- **clean.sh**: 清理所有构建产物和缓存