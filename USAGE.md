# 📖 Usage Guide for XFakeContrib

This guide explains how to use the main components of **XFakeContrib** to generate fake commits and manage your repositories.

---

## 🎨 Theme Manager

Customize the appearance of the application by switching between different themes.

---

## 👤 User Manager

If you want to see your GitHub contribution graph on <b>Contributions</b>, you need to set token and username. But it's not a must for creating commits.

Manage your **GitHub user** and **authentication**.

1. **Enter your GitHub Username** and **Personal Access Token (PAT)**:
   - Go to [GitHub Settings - Tokens](https://github.com/settings/tokens) and create a token with the following permissions:
     - `repo/repo:status`
     - `repo/public_repo`
2. **Paste the token** and your GitHub Username then **click `Validate`**.
3. Once validated, your contribution graph will be displayed on the **Contributions**.

---

## 📊 Contributions

View and interact with your **GitHub contribution graph**.

- **Left-click** a day to set it as the **Start Date** in Repositories.
- **Right-click** a day to set it as the **End Date**.
- **Middle-click** a day to set both Start and End Dates together.
- **Hover over** a day to see the number of contributions.
- **Click `Reload`** to refresh your contribution data.

---

## 📂 Repository Manager

Manage your local repositories for commit generation.

- **Add**, **Update**, and **Delete** repositories.
- Manage branches of a selected repository:
  - Create new branches.
  - Rename existing branches.
  - Delete branches.

---

## 📦 Repositories

Perform the main operations for commit creation and management.

### Managing Repositories
- All repositories added from <b>Repository Manager</b> will appear here.
- You can **activate** one or more repositories by selecting them in the table.

### Selecting Files
- After enabling at least one repository, click **`File`** button for each enabled repository to select the file that will be used for creating commits.

### Branch Selection
- You can **change the target branch** for commits directly in the repository table.

### Push and Log Operations
- **Push**: Push commits to the remote repository (no need to enable repository).
- **Log**: View recent logs of a repository (no need to enable repository).

---

## 🛠️ Creating Commits

Fill in the settings under the RepositoryCard:

- **Commit Count**:
  - Set a static number or enable **Random** (checkbox).
  - Right-click the Random checkbox to set a **maximum random commit count**.
- **Date Range**:
  - Choose **Start** and **End** dates manually.
  - Enable **Today** checkbox to set both dates to today.
- **Commit Message**:
  - Write a custom message(static) or enable **Random** (checkbox) for automatic message generation.
- **Commit Content**:
  - Write custom content(static) or enable **Random** (checkbox) for automatic content generation.

Once all settings are ready:

- Click **`Create Commits`** to generate commits between the selected dates.
- If multiple repositories are active, commits are **distributed and processed in parallel**.

---

## 🚀 Pushing Commits

- After creating commits, click **`Push All`** to push all active repositories at once.

---

# 📢 Additional Notes

- If you prefer, you can set the dates interactively using the ContribCard graph by clicking on the desired day.
- Contributions will be spread across your repositories depending on the commit date range.
- You don't need to set token and username in <b>User Manager</b> to creating fake commits.