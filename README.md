<div id="top">

<!-- HEADER STYLE: CLASSIC -->
<div align="center">

<img src="assets/pngegg.png" width="17%" style="position: relative; top: 0; right: 0;" alt="Project Logo"/>

# <code> ARCADE </code>

<em></em>

<!-- BADGES -->
<!-- local repository, no metadata badges. -->

<em>Built with the tools and technologies:</em>

<img src="https://img.shields.io/badge/CMake-064F8C.svg?style=default&logo=CMake&logoColor=white" alt="CMake">
<img alt="Static Badge" src="https://img.shields.io/badge/sfml-green?style=plastic&logo=appveyor&logoColor=green&logoSize=auto">
<img alt="Static Badge" src="https://img.shields.io/badge/ncurses-black?style=flat&logo=ncurses&logoColor=white">
<img alt="Static Badge" src="https://img.shields.io/badge/cpp-blue?style=flat&logo=c%2B%2B&logoColor=white">


</div>
<br>

---

## Table of Contents

- [Table of Contents](#table-of-contents)
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
    - [Project Index](#project-index)
- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Installation](#installation)
    - [Usage](#usage)
    - [Testing](#testing)
- [Roadmap](#roadmap)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgments](#acknowledgments)

---

## Overview

Arcade is a gaming platform : a program that lets the user choose a game to play and keeps a register of
player scores.

To be able to deal with the elements of your gaming plateform at run-time, your graphics libraries and
your games must be implemented as dynamic libraries, loaded at run-time. Each GUI available for the
program must be used as a shared library that will be loaded and used dynamically by the main program.
This also applies to your games.

---

## Features

<code>❯ Dynamic libraries</code><br>
<code>❯ Graphic libraries</code><br>
<code>❯ Games </code><br>

---

## Project Structure

```sh
└── /
    ├── CMakeLists.txt
    ├── include
    │   ├── game
    │   └── graphics
    └── src
        ├── graphics
        └── main.cpp
```

### Project Index

<details open>
	<summary><b><code>/</code></b></summary>
	<!-- __root__ Submodule -->
	<details>
		<summary><b>__root__</b></summary>
		<blockquote>
			<div class='directory-path' style='padding: 8px 0; color: #666;'>
				<code><b>⦿ __root__</b></code>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='/CMakeLists.txt'>CMakeLists.txt</a></b></td>
					<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
				</tr>
			</table>
		</blockquote>
	</details>
	<!-- src Submodule -->
	<details>
		<summary><b>src</b></summary>
		<blockquote>
			<div class='directory-path' style='padding: 8px 0; color: #666;'>
				<code><b>⦿ src</b></code>
			<table style='width: 100%; border-collapse: collapse;'>
			<thead>
				<tr style='background-color: #f8f9fa;'>
					<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
					<th style='text-align: left; padding: 8px;'>Summary</th>
				</tr>
			</thead>
				<tr style='border-bottom: 1px solid #eee;'>
					<td style='padding: 8px;'><b><a href='/src/main.cpp'>main.cpp</a></b></td>
					<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
				</tr>
			</table>
			<!-- graphics Submodule -->
			<details>
				<summary><b>graphics</b></summary>
				<blockquote>
					<div class='directory-path' style='padding: 8px 0; color: #666;'>
						<code><b>⦿ src.graphics</b></code>
					<!-- SDL2 Submodule -->
					<details>
						<summary><b>SDL2</b></summary>
						<blockquote>
							<div class='directory-path' style='padding: 8px 0; color: #666;'>
								<code><b>⦿ src.graphics.SDL2</b></code>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='/src/graphics/SDL2/SDL2.cpp'>SDL2.cpp</a></b></td>
									<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- ncurses Submodule -->
					<details>
						<summary><b>ncurses</b></summary>
						<blockquote>
							<div class='directory-path' style='padding: 8px 0; color: #666;'>
								<code><b>⦿ src.graphics.ncurses</b></code>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='/src/graphics/ncurses/Ncurses.cpp'>Ncurses.cpp</a></b></td>
									<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
		</blockquote>
	</details>
	<!-- include Submodule -->
	<details>
		<summary><b>include</b></summary>
		<blockquote>
			<div class='directory-path' style='padding: 8px 0; color: #666;'>
				<code><b>⦿ include</b></code>
			<!-- graphics Submodule -->
			<details>
				<summary><b>graphics</b></summary>
				<blockquote>
					<div class='directory-path' style='padding: 8px 0; color: #666;'>
						<code><b>⦿ include.graphics</b></code>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='/include/graphics/IGraphic.hpp'>IGraphic.hpp</a></b></td>
							<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
						</tr>
					</table>
					<!-- SDL2 Submodule -->
					<details>
						<summary><b>SDL2</b></summary>
						<blockquote>
							<div class='directory-path' style='padding: 8px 0; color: #666;'>
								<code><b>⦿ include.graphics.SDL2</b></code>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='/include/graphics/SDL2/SDL2.hpp'>SDL2.hpp</a></b></td>
									<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
								</tr>
							</table>
						</blockquote>
					</details>
					<!-- ncurses Submodule -->
					<details>
						<summary><b>ncurses</b></summary>
						<blockquote>
							<div class='directory-path' style='padding: 8px 0; color: #666;'>
								<code><b>⦿ include.graphics.ncurses</b></code>
							<table style='width: 100%; border-collapse: collapse;'>
							<thead>
								<tr style='background-color: #f8f9fa;'>
									<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
									<th style='text-align: left; padding: 8px;'>Summary</th>
								</tr>
							</thead>
								<tr style='border-bottom: 1px solid #eee;'>
									<td style='padding: 8px;'><b><a href='/include/graphics/ncurses/Ncurses.hpp'>Ncurses.hpp</a></b></td>
									<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
								</tr>
							</table>
						</blockquote>
					</details>
				</blockquote>
			</details>
			<!-- game Submodule -->
			<details>
				<summary><b>game</b></summary>
				<blockquote>
					<div class='directory-path' style='padding: 8px 0; color: #666;'>
						<code><b>⦿ include.game</b></code>
					<table style='width: 100%; border-collapse: collapse;'>
					<thead>
						<tr style='background-color: #f8f9fa;'>
							<th style='width: 30%; text-align: left; padding: 8px;'>File Name</th>
							<th style='text-align: left; padding: 8px;'>Summary</th>
						</tr>
					</thead>
						<tr style='border-bottom: 1px solid #eee;'>
							<td style='padding: 8px;'><b><a href='/include/game/IGame.hpp'>IGame.hpp</a></b></td>
							<td style='padding: 8px;'>Code>❯ REPLACE-ME</code></td>
						</tr>
					</table>
				</blockquote>
			</details>
		</blockquote>
	</details>
</details>

---

## Getting Started

### Prerequisites

This project requires the following dependencies:

- **Programming Language:** CPP
- **Package Manager:** Cmake

### Installation

Build  from the source and intsall dependencies:

1. **Clone the repository:**

 ```sh
git clone ../
 ```

2. **Navigate to the project directory:**

```sh
cd 
```

3. **Install the dependencies:**

<!-- SHIELDS BADGE CURRENTLY DISABLED -->
	<!-- [![cmake][cmake-shield]][cmake-link] -->
	<!-- REFERENCE LINKS -->
	<!-- [cmake-shield]: https://img.shields.io/badge/C++-00599C.svg?style={badge_style}&logo=c%2B%2B&logoColor=white -->
	<!-- [cmake-link]: https://isocpp.org/ -->

	**Using [cmake](https://isocpp.org/):**

	```sh
	cmake . && make
	```

### Usage

Run the project with:

**Using [cmake](https://isocpp.org/):**
```sh
cmake --build .
./arcade ./lib/*.so
```

### Testing

 uses the {__test_framework__} test framework. Run the test suite with:

**Using [cmake](https://isocpp.org/):**
```sh
ctest
```

---

## Roadmap

- [X] **`Task 1`**: <strike>Implement libarcade.</strike>
- [X] **`Task 2`**: <strike>Pick two games.</strike>
- [X] **`Task 3`**: <strike>Make maths methods to display these games.</strike>
- [X] **`Task 4`**: <strike>Develop both games.</strike>
- [X] **`Task 5`**: <strike>Implement robustness and parsing tests.</strike>
- [ ] **`Task 6`**: Implement games tests.

---

## Contributing

- **💬 [Join the Discussions](https://LOCAL///discussions)**: Share your insights, provide feedback, or ask questions.
- **🐛 [Report Issues](https://LOCAL///issues)**: Submit bugs found or log feature requests for the `` project.
- **💡 [Submit Pull Requests](https://LOCAL///blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your LOCAL account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone ./
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to LOCAL**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://LOCAL{///}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=/">
   </a>
</p>
</details>

---

## License

 is protected under the [LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

## Acknowledgments

- Credit `contributors: Mateoantoni, AdryzR, RvbyY`, `inspiration: arcade stations`, `references: School project`
         `Interface collaborators group leaders: ` **pierre.cufer@epitech.eu** ` (selected as collaboration partner for grading), ` **christophe.dronne@epitech.eu**, **maryam.larsanova@epitech.eu**

<div align="right">

[![][back-to-top]](#top)

</div>


[back-to-top]: https://img.shields.io/badge/-BACK_TO_TOP-151515?style=flat-square


---
