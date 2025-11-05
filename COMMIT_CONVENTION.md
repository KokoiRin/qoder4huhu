# Git 提交规范

## 提交消息格式

遵循 [Conventional Commits](https://www.conventionalcommits.org/) 规范：

```
<type>(<scope>): <subject>

<body>

<footer>
```

### Type 类型

- `feat`: 新功能
- `fix`: 修复 bug
- `docs`: 文档变更
- `style`: 代码格式（不影响代码运行）
- `refactor`: 重构（既不是新功能也不是修复 bug）
- `perf`: 性能优化
- `test`: 添加或修改测试
- `build`: 构建系统或外部依赖变更
- `ci`: CI 配置文件和脚本变更
- `chore`: 其他不修改 src 或 test 文件的变更

### Scope 范围（可选）

- `DataLayer`
- `ServiceLayer`
- `PresentationLayer`
- `UILayer`
- `Common`
- `test`

### 示例

```bash
# 简单提交
git commit -m "feat(DataLayer): add window screenshot feature"

# 详细提交
git commit -m "fix(MouseSimulator): correct click coordinate calculation

- Fixed off-by-one error in coordinate transformation
- Added boundary checking
- Updated unit tests

Closes #123"
```

## 分支命名规范

```
<type>/<short-description>
```

### 示例

```bash
git checkout -b feat/window-capture
git checkout -b fix/mouse-click-offset
git checkout -b refactor/keyboard-api
git checkout -b docs/update-readme
```
