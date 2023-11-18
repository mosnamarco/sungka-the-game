# Sungka: The Game

* [Introduction](#introduction)
* [For Users](#for-users)
* [For Developers](#for-contributing-developers)

## Introduction

Sungka: The Game is based on a real life Filipino game called "Sungka". According to wikipedia; Southeast Asian mancalas are a subtype of mancala games predominantly found in Southeast Asia. They are known as congklak (VOS Spelling: tjongklak), congkak, congka, and dakon in Indonesia, congkak in Malaysia and Brunei, and sungkâ in the Philippines. They differ from other mancala games in that the player's store is included in the placing of the seeds. Like other mancalas, they vary widely in terms of the rules and number of holes used.

## Game Rules

The rules for the most common seven-hole mancala versions in Brunei, Indonesia, Malaysia, the Maldives, Marianas, and the Philippines are almost identical. Each player controls the seven holes on the side of the board to their left, and their score is the number of seeds in their store holes. Seven seeds are placed in each small hole except for the players' store hole. The objective of the game is to capture more seeds in the store than one's opponent.

Both players begin simultaneously by scooping up all the seeds in any hole on their side. Each drops a seed into the next hole and continues clockwise depositing one seed into every hole thereafter. A player drops a seed into their store each time they pass it but does not deposit any into their opponent's store.

How the game continues, depends on where the last seed of each scoop is deposited.

* If the seed drops into the player’s own store: the player scoops up the seeds from any of their holes and distributes them in the holes round the board but not in their opponent's store.

* If the seed drops into a hole (on either side of the board) containing seed: The player scoops up all of the seeds in that hole and continues distributing them as described above.

* If the seed drops into the player’s hole which is without seeds: The player is entitled to collect the seeds in their opponent's store directly opposite their own. These seeds collected from their opponent's holes together with their last seed are deposited in their own store. If the opponent's store opposite their own is empty, they deposit only their last seed in their own store. They forfeit their turn and stop playing. It is the opponent's turn now to distribute the seeds.

* If the seed drops into an empty hole belonging to the opponent: the player forfeits their turn and stops playing. They also forfeit their seeds and leave it in the opponent's hole. It is the opponent's turn now to distribute the seeds.

The first round ends when a player has no more seeds in their holes. The remaining seeds are awarded to their opponent.

Play resumes in the second round with players redistributing seeds from their own store to their own holes. Beginning from left to right, seven seeds are placed in each hole. If a player does not have sufficient seeds to fill their own holes, the remaining holes are left empty and are considered 'burnt'. The leftover seeds are deposited into their own store. The opponent deposits excess seeds they have won into their own store.

The loser gets to start the second round. Play is continued as before but players will bypass 'burnt' holes and no seeds are to be dropped into these holes. If a seed is accidentally dropped into a 'burnt' holes, it is confiscated and stored in the opponent's store.

Play continues until one player loses all of their holes or concedes defeat.

source: [Wikipedia](https://en.wikipedia.org/wiki/Southeast_Asian_mancala)

## For users

**Quickstart**

1. `git clone <repository link>`
2. `cd <cloned repository directory>`
3. `make`
4. run server `./dist/server`
5. run client `./dist/client`

## For contributing developers

<small>

<div style="text-align: center;"> 
  
  **_Note to contributing developers_**

</div>

_Pull Requests and Merge Requests:_

  After creating your branch, **always pull from the main branch to avoid merge conflicts**. But having merge conflicts are unavoidable if two contributors work on something and both created a pull request at the same time. To fix this, the first one to create the pull request (chronologically), will be checked, and if accepted, merged to the main branch. After this, the second one who created a pull request must update their code by pulling and reolving merge conflicts locally before creating another pull request to the main branch. In a scenario where the first pull request is denied, the next in queue of pull requests will be checked and so on...

_Branching:_

  **After the PR(s)/MR(s) made on your branch to the main branch is/are successful, create a new branch to start a new integration**. This solves the problem of mislabeling branches. These mislabeling problems occur when a branch named "bugfix/server-connection-issue" submitted a pull request but the contents of the commits/branch are about editing the .MD file for example. Although it does not affect the output of the project, it is annoying to review a misleading branch since you will be misguided and check the wrong things thus making the job longer than it should be. 
</small>

<hr>

**Creating Branches**

Before creating/modifying a feature, adding/removing files, or generating a patch or bugfix, create a branch to avoid merge conflicts and for easy management. More specifically, follow #2 from [TilburgScienceHub: Best Practices for Naming Git Branches](https://tilburgsciencehub.com/building-blocks/collaborate-and-share-your-work/use-github/naming-git-branches/)

| Category | Meaning                                               |
|----------|-------------------------------------------------------|
| hotfix   | For quickly fixing critical issues, usually with a temporary solution |
| bugfix   | For fixing a bug                                      |
| feature  | For adding, removing, or modifying a feature           |
| test     | For experimenting with something which is not an issue |
| wip      | For a work in progress                                 |

example code snippet for creating a branch for a bugfix:

`git branch bugfix/server-connection-issue`
or
`git checkout -b bugfix/server-connection-issue` 

**Pull Requests**

`git pull origin <branch name>`

**Creating Commits**

For creating commits, refer to [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)

| Commit Type         | Description                                                                                              | Semantic Versioning Equivalent |
|---------------------|----------------------------------------------------------------------------------------------------------|-------------------------------|
| fix                 | A commit that patches a bug in the codebase.                                                               | PATCH                         |
| feat                | A commit that introduces a new feature to the codebase.                                                     | MINOR                         |
| BREAKING CHANGE     | A commit introducing a breaking API change indicated by a footer `BREAKING CHANGE:` or `!` after type/scope.| MAJOR                         |
| build               | A commit related to building processes or tools configuration.                                              | -                             |
| chore               | A commit that involves changes to tasks or maintenance activities.                                          | -                             |
| ci                  | A commit related to continuous integration or deployment.                                                    | -                             |
| docs                | A commit that includes documentation changes.                                                               | -                             |
| style               | A commit that addresses code styling/formatting (whitespace, formatting, etc.).                             | -                             |
| refactor            | A commit that involves code restructuring without changes in functionality.                                 | -                             |
| perf                | A commit that improves code performance.                                                                    | -                             |
| test                | A commit related to tests or testing frameworks.                                                             | -                             |
| and others...       | Additional commit types may be used based on specific project requirements or conventions.                  | -                             |

Commit message template
```
<type>[optional scope]: <description>
[optional body]
[optional footer(s)]
```
or
`<type>: <description>`

Example
```
git commit -m "
fix: fixed connection errors

Introduced new library <examplelib.h> and removed <oldlib.h>

Created a headerfile <something.h> for sungka functionalities
"
```
or 
`git commit -m "feat: allowed 3 client connections to server"`

