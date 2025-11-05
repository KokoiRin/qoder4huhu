# GitHub Branch Protection Configuration Guide
# GitHub 分支保护规则配置指南

## 配置步骤

### 1. 访问仓库设置
1. 打开你的 GitHub 仓库: https://github.com/KokoiRin/qoder4huhu
2. 点击顶部的 **Settings** (设置)
3. 在左侧菜单中选择 **Branches** (分支)

### 2. 配置分支保护规则
点击 **Add rule** (添加规则) 或编辑现有规则

#### 分支名称模式
```
master
```
如果有其他主分支（如 `main` 或 `develop`），也需要分别配置。

#### 必须启用的规则

##### ✅ Require a pull request before merging
**要求在合并前创建 Pull Request**
- 勾选此项
- 子选项:
  - ✅ **Require approvals**: 至少 1 个审批
  - ✅ **Dismiss stale pull request approvals when new commits are pushed**: 新提交时撤销旧审批
  - ✅ **Require review from Code Owners**: 需要代码所有者审查（可选）
  - ⚠️ **Require approval of the most recent reviewable push**: 要求审批最新的推送

##### ✅ Require status checks to pass before merging
**要求状态检查通过后才能合并**
- 勾选此项
- 子选项:
  - ✅ **Require branches to be up to date before merging**: 要求分支是最新的
  - 搜索并添加状态检查:
    - `code-quality` (来自 GitHub Actions)

##### ✅ Require conversation resolution before merging
**要求解决所有对话后才能合并**
- 勾选此项

##### ⚠️ Do not allow bypassing the above settings
**不允许绕过上述设置**
- ✅ 勾选此项（重要！）
- ⚠️ 即使是管理员也必须遵守规则

##### ✅ Include administrators
**规则适用于管理员**
- ✅ 勾选此项
- 这样你自己提交的代码也需要经过审查流程

### 3. 其他推荐设置

#### ✅ Require linear history
**要求线性提交历史**
- 勾选此项可以保持干净的提交历史

#### ✅ Require signed commits (可选)
**要求签名提交**
- 提高安全性，但需要配置 GPG 密钥

#### ✅ Lock branch
**锁定分支** (可选)
- 如果需要完全禁止直接推送，可以勾选

### 4. 保存配置
点击页面底部的 **Create** 或 **Save changes** 保存规则

## 工作流程

配置完成后，你的工作流程将是：

1. **创建特性分支**
   ```bash
   git checkout -b feature/your-feature
   ```

2. **开发并提交代码**
   ```bash
   git add .
   git commit -m "feat: your feature"
   # pre-commit hook 会自动检查代码格式
   ```

3. **推送到远程仓库**
   ```bash
   git push origin feature/your-feature
   ```

4. **在 GitHub 创建 Pull Request**
   - 访问仓库页面
   - 点击 "Pull requests" -> "New pull request"
   - 选择 `master` <- `feature/your-feature`
   - 填写 PR 描述

5. **等待 CI 检查通过**
   - GitHub Actions 会自动运行代码质量检查
   - 检查包括：格式化、静态分析、测试

6. **代码审查**
   - 即使是你自己的提交，也需要在 GitHub 页面进行审查
   - 点击 PR 中的 "Files changed" 查看代码变更
   - 添加评论或建议
   - 点击 "Review changes" -> "Approve"

7. **合并代码**
   - 审批通过且所有检查都通过后
   - 点击 "Merge pull request"

## 绕过保护（紧急情况）

如果确实需要绕过检查（不推荐）：

```bash
# 跳过 pre-commit hook
git commit --no-verify -m "emergency fix"

# 但你仍然需要在 GitHub 上创建 PR 并审查
```

## 注意事项

1. **不能直接推送到 master**
   ```bash
   # 这将被拒绝
   git push origin master
   ```

2. **必须通过 Pull Request 工作流**
   - 所有代码变更都需要 PR
   - 包括你自己的提交

3. **CI 检查失败时无法合并**
   - 必须修复所有格式问题
   - 必须通过静态分析

4. **即使是管理员也必须遵守规则**
   - 这是你要求的配置
   - 确保代码质量一致性

## 团队协作（可选）

如果以后有团队成员加入：

1. **添加 CODEOWNERS 文件**
   创建 `.github/CODEOWNERS`:
   ```
   # 代码所有者配置
   * @KokoiRin
   
   # 特定目录可以指定不同的审查者
   /DataLayer/ @KokoiRin
   /ServiceLayer/ @KokoiRin
   ```

2. **配置团队审查**
   - Settings -> Manage access
   - 添加协作者或创建团队
