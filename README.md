
## Git Subtree Shared Code Management Guide

### 1. Purpose

This guide defines how multiple projects can share and maintain CUtilities
source code using Git Subtree.

The goals are to:

-   Maintain the shared code in its own Git repository.
-   Reuse the same shared code across multiple projects.
-   Keep a complete copy of the shared source files inside each
    consuming project.
-   Allow each parent project to track every file under `CUtilities/` as
    ordinary files.
-   Update shared code from the central repository when needed.
-   Push generally useful changes made in a project back to the central
    repository.
-   Keep projects independently cloneable, buildable, and deployable
    without downloading a separate submodule.

### 2. Architecture

#### 2.1 Repository layout

The shared repository (`CUtilities`) contains the contents that will appear
inside the `CUtilities/` directory of each consuming project:

``` text
CUtilities/
├── src/
│   ├── logger/
│   ├── utils/
│   ├── database/
│   └── config/
├── tests/
├── README.md
├── CHANGELOG.md
└── VERSION
```

A consuming project looks like this:

``` text
project-a/
├── .git/
├── src/
├── config/
├── CUtilities/
│   ├── src/
│   ├── tests/
│   ├── README.md
│   ├── CHANGELOG.md
│   └── VERSION
├── scripts/
│   ├── sync-CUtilities.sh
│   └── push-CUtilities.sh
└── GIT_SUBTREE_GUIDE.md
```

#### 2.2 Core principles

1.  The `CUtilities` repository is the canonical source for shared code.
2.  In each consuming project, `CUtilities/` is a normal directory tracked
    by the parent repository.
3.  The `CUtilities/` directory does not contain its own `.git` directory.
4.  Git Subtree is used to synchronize the directory with the
    independent `CUtilities` repository.
5.  General-purpose changes made in a consuming project should
    eventually be sent back to the shared repository.
6.  Each consuming project can develop, commit, release, and deploy
    independently.
7.  Projects may choose when to synchronize shared code.

### 3. Repository configuration

Example repository URLs:

``` text
CUtilities:
https://github.com/yourname/CUtilities.git

Project A:
https://github.com/yourname/project-a.git

Project B:
https://github.com/yourname/project-b.git
```

Default configuration:

``` text
Remote name: CUtilities
Upstream branch: main
Subtree prefix: CUtilities
```

Each consuming project should configure the `CUtilities` remote.

### 4. Initialize a consuming project

Run these steps once for each project.

#### 4.1 Clone the project

``` bash
git clone https://github.com/yourname/project-a.git
cd project-a
```

#### 4.2 Add the shared repository as a remote

``` bash
git remote add CUtilities https://github.com/yourname/CUtilities.git
```

Verify the remotes:

``` bash
git remote -v
```

You should see both `origin` and `CUtilities`.

#### 4.3 Fetch the shared repository

``` bash
git fetch CUtilities
```

#### 4.4 Add the shared code as a subtree

``` bash
git subtree add \
  --prefix=CUtilities \
  CUtilities main \
  --squash
```

After this command, all files from the root of the `CUtilities` repository
will be present under `CUtilities/` in the consuming project.

Parameter meanings:

-   `--prefix=CUtilities`: destination directory in the consuming project.
-   `CUtilities`: remote name of the shared repository.
-   `main`: branch to import.
-   `--squash`: records the imported changes as a squashed integration
    commit instead of bringing every upstream commit into the consuming
    project's visible history.

Repeat the same initialization process for other consuming projects.

**Important:** The target directory must not already contain unrelated
files. If `CUtilities/` already exists, inspect and back it up before
running `git subtree add`.

### 5. Synchronize shared code into a project

When the shared repository receives new commits, update a consuming
project with:

``` bash
git fetch CUtilities

git subtree pull \
  --prefix=CUtilities \
  CUtilities main \
  --squash
```

Recommended practices:

-   Start from the intended project branch.
-   Commit or stash local work before synchronizing.
-   Review the resulting changes.
-   Run the project's tests.
-   Commit and push the updated project history to its `origin` remote.

The parent project stores the actual files under `CUtilities/`; it does not
store only a submodule pointer.

### 6. Send shared-code changes back upstream

If you make a generally useful change under `CUtilities/`, you can send it
back to the shared repository.

#### 6.1 Commit the change in the consuming project

``` bash
git add CUtilities
git commit -m "fix: update CUtilities CUtilities"
```

#### 6.2 Push the subtree to the shared repository

``` bash
git subtree push \
  --prefix=CUtilities \
  CUtilities main
```

Only changes that are genuinely reusable should be sent upstream.
Project-specific business logic should remain in the consuming project.

For team workflows, prefer pushing changes to a dedicated branch in the
shared repository and opening a pull request into `main`, rather than
pushing directly to `main`.

Before pushing, coordinate with other contributors and fetch the latest
upstream changes. Concurrent edits to the same files may require
conflict resolution.

### 7. Automation scripts

Each consuming project can include these helper scripts:

``` text
scripts/
├── sync-CUtilities.sh
└── push-CUtilities.sh
```

Make the scripts executable on macOS/Linux:

``` bash
chmod +x scripts/sync-CUtilities.sh
chmod +x scripts/push-CUtilities.sh
```

#### 7.1 `scripts/sync-CUtilities.sh`

This script fetches and merges the latest `main` branch from the shared
repository.

``` bash
#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

PREFIX="CUtilities"
REMOTE="CUtilities"
BRANCH="main"

# Require a clean working tree, including untracked files.
if [[ -n "$(git status --porcelain)" ]]; then
    echo "Error: working tree is not clean."
    echo "Please commit, stash, or otherwise resolve your changes first."
    exit 1
fi

# Fetch the latest shared code.
git fetch "$REMOTE" "$BRANCH"

# Merge the shared code into the project.
git subtree pull \
    --prefix="$PREFIX" \
    "$REMOTE" \
    "$BRANCH" \
    --squash

echo "CUtilities synchronized successfully."
```

Run it with:

``` bash
./scripts/sync-CUtilities.sh
```

#### 7.2 `scripts/push-CUtilities.sh`

This script pushes the subtree content back to the shared repository.

``` bash
#!/usr/bin/env bash
set -euo pipefail

ROOT="$(git rev-parse --show-toplevel)"
cd "$ROOT"

PREFIX="CUtilities"
REMOTE="CUtilities"
BRANCH="main"

# Ensure there are no uncommitted changes under CUtilities/.
if ! git diff --quiet -- "$PREFIX" ||
   ! git diff --cached --quiet -- "$PREFIX"; then
    echo "Error: CUtilities has uncommitted changes."
    echo "Please commit the CUtilities changes first."
    exit 1
fi

# Push the subtree to the shared repository.
git subtree push \
    --prefix="$PREFIX" \
    "$REMOTE" \
    "$BRANCH"

echo "CUtilities pushed successfully."
```

Run it with:

``` bash
./scripts/push-CUtilities.sh
```

Before running this script, verify that the commits being pushed contain
only changes intended for the shared repository. In particular, avoid
accidentally publishing project-specific changes from `CUtilities/`.

### 8. Commit-time synchronization policy

Do not run `git subtree pull` directly inside a `pre-commit` hook.

A subtree pull can create a merge commit and modify the working tree and
index. Running that operation during another commit's hook can make the
commit process confusing or unsafe.

Recommended workflow:

``` bash
# 1. Synchronize shared code.
./scripts/sync-CUtilities.sh

# 2. Develop the project.

# 3. Commit project changes.
git add .
git commit -m "feat: add new feature"

# 4. Push the project.
git push origin main
```

If automatic checking is desired, a `pre-commit` hook may check whether
the upstream shared branch has advanced and reject the commit with
instructions to run `sync-CUtilities.sh`. The hook should not perform the
subtree merge itself.

A plain `git commit` does not automatically run a wrapper script. If a
team wants synchronization to happen before every commit, use a
documented command or a carefully maintained commit wrapper.

### 9. Conflict resolution

Conflicts can occur when multiple projects or contributors modify the
same shared files.

For example:

-   Project A modifies `CUtilities/Utils.py`.
-   Project B independently modifies `CUtilities/Utils.py`.
-   Both changes are sent upstream or one project synchronizes after the
    other.

Start by fetching and attempting the normal synchronization:

``` bash
git fetch CUtilities

git subtree pull \
  --prefix=CUtilities \
  CUtilities main \
  --squash
```

If Git reports conflicts:

``` bash
# Inspect the conflicted files.
git status

# Edit the files and resolve the conflict.

# Mark the resolved files.
git add CUtilities

# Complete the merge if Git has not already completed it.
git commit
```

Then run relevant tests.

Do not resolve conflicts by blindly replacing the entire `CUtilities/`
directory. Doing so may discard valid changes from another contributor.

### 10. Versioning shared code

Use semantic versioning for formal shared-code releases, for example:

``` text
v1.0.0
v1.1.0
v1.2.0
v2.0.0
```

Create and push a release tag in the shared repository:

``` bash
cd CUtilities

git tag -a v1.0.0 -m "CUtilities v1.0.0"
git push origin v1.0.0
```

A consuming project can choose either:

-   **Track `main`:** synchronize the latest development code.
-   **Track a tag:** synchronize a specific stable release.

For example, to synchronize a specific tag:

``` bash
git fetch CUtilities --tags

git subtree pull \
  --prefix=CUtilities \
  CUtilities v1.1.0 \
  --squash
```

For production projects, prefer stable tags or otherwise record the
exact upstream commit used. Development projects may track `main`.

### 11. Rollback

If a subtree synchronization introduces a problem, identify the
integration commit:

``` bash
git log --oneline
```

Then revert it:

``` bash
git revert <commit-id>
```

Reverting preserves shared Git history and is generally safer than
rewriting commits that have already been pushed.

After reverting, run the project tests and push the revert commit as
appropriate.

### 12. Build and deployment

Because the shared code is stored directly in the consuming project's
repository, a normal clone includes it:

``` bash
git clone https://github.com/yourname/project-a.git
```

No submodule initialization is required.

Build and deployment pipelines can use `CUtilities/` directly. For example:

``` dockerfile
FROM python:3.12-slim

WORKDIR /app

COPY . .

RUN pip install -r requirements.txt

CMD ["python", "src/main.py"]
```

The `COPY` instruction includes `CUtilities/` along with the rest of the
project.

**Do not automatically pull the latest shared code during a production
deployment.** Deploy a tested project commit that already contains the
intended CUtilities version. This makes deployments reproducible.

### 13. CUtilities Git commands

|                          |                                                                   |
|Operation                 |          Command                                                  |
|--------------------------|-------------------------------------------------------------------|
|Add shared remote         |          `git remote add CUtilities URL`                              |
|Fetch shared repository   |          `git fetch CUtilities`                                       | 
|Add subtree initially     |          `git subtree add --prefix=CUtilities CUtilities main --squash`   |
|Pull shared updates       |          `git subtree pull --prefix=CUtilities CUtilities main --squash`  |
|Push shared changes       |          `git subtree push --prefix=CUtilities CUtilities main`           |
|List remotes              |          `git remote -v`                                          |
|Check working tree        |          `git status`                                             |
|View commit history       |          `git log --oneline`                                      |
|Revert a commit           |          `git revert COMMIT_ID`                                   |
|                          |                                                                    |

### 14. Operating rules

#### Shared repository

-   Owns the canonical shared source code.
-   Maintains and tests reusable functionality.
-   Keeps `main` stable.
-   Uses tags for formal releases.
-   Reviews changes before merging them into `main`.
-   Avoids depending on project-specific business logic.

#### Consuming projects

-   Manage `CUtilities/` using Git Subtree.
-   Track all files under `CUtilities/` in the parent repository.
-   Synchronize shared code deliberately and regularly.
-   Keep project-specific logic outside `CUtilities/`.
-   Send generally useful changes back upstream.
-   Test after synchronization.
-   Deploy a committed and tested project revision.

### 15. Key principle

**The `CUtilities` repository is the canonical source of shared code. Each
consuming project contains a complete, independently tracked copy of
that code under `CUtilities/`. Git Subtree provides the synchronization
mechanism between the shared repository and each project.**

This approach provides independent maintenance of shared code, full file
tracking in each parent project, and straightforward cloning, building,
and deployment without Git Submodules.
