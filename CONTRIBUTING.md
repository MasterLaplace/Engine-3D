# CONTRIBUTING GUIDELINES

Engine-3D is a Epitech Student project. Contribution is welcome, encouraged, and appreciated.
It is also essential for the development of the project.

See the [Table of Contents](#table-of-contents) for different ways to help and details about how this project handles them. Please make sure to read the relevant section before making your contribution. It will make it a lot easier for us maintainers and smooth out the experience for all involved. The community looks forward to your contributions. 🎉

> And if you like the project, but just don't have time to contribute, that's fine. There are other easy ways to support the project and show your appreciation, which we would also be very happy about:
> - Star the project
> - Tweet about it
> - Refer this project in your project's readme
> - Mention the project at local meetups and tell your friends/colleagues
> - Become a [Sponsor](.github/FUNDING.md)

----

## Table of Contents

1. [Introduction](#introduction)
2. [Code of Conduct](#code-of-conduct)
3. [How to Contribute](#how-to-contribute)
    - [Creating an Issue](#creating-an-issue)
    - [Creating a Pull Request](#creating-a-pull-request)
    - [Improve the Documentation](#improve-the-documentation)
4. [Project Structure](#project-structure)
    - [Technical Documentation](#technical-documentation)
    - [Laplace Libraries](#laplace-libraries)
5. [Commit Guidelines](#commit-guidelines)
    - [Format](#format)
    - [Style](#style)
6. [Support and Contact](#support-and-contact)

----

## Introduction

Here, you can provide a brief overview of what the Engine-3D project is about and why contributions are important.

v0.0.1 of the project is currently under development. You can find the latest release [here]().

----

## Code of Conduct

Make sure to read and understand our [Code of Conduct](.github/CODE_OF_CONDUCT.md). Anyone contributing to this project must adhere to these guidelines.

----

## How to Contribute

### Creating an Issue

Before contributing, make sure to check if there's an existing issue for the task you want to work on. If not, [create a new issue](https://github.com/MasterLaplace/Engine-3D/issues/new) to discuss your proposal. This will help us maintainers to give you feedback and suggestions on your work.

### Creating a Pull Request

When you're ready to contribute, follow our guide on [creating a Pull Request](.github/PULL_REQUEST_TEMPLATE.md). Make sure to read the guide carefully and follow the instructions. This will make it easier for us to review your Pull Request.

### Improve the Documentation

If you find any mistakes or want to improve the documentation, you can do so by clicking the **Edit** button on the top right corner of the page. This will take you to the GitHub page for the documentation file you're currently viewing. You can then make your changes and create a Pull Request.

----

## Project Structure

### Technical Documentation

For technical documentation, please refer to the project's GitHub wiki. You can find more information there on how the project works.

### Laplace Libraries

If you're contributing to the Laplace Libraries module, make sure to consult the documentation in this section to understand how it functions.

## Commit Guidelines

Engine-3D uses the [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/)
specification. The automatic changelog tool uses these to automatically generate
a changelog based on the commit messages. Here's a guide to writing a commit message
to allow this:

### Format

```
type(scope)!: subject
```

- `type`: the type of the commit is one of the following:

  - `feat`: new features.
  - `fix`: bug fixes.
  - `docs`: documentation changes.
  - `refactor`: refactor of a particular code section without introducing
    new features or bug fixes.
  - `style`: code style improvements.
  - `perf`: performance improvements.
  - `test`: changes to the test suite.
  - `ci`: changes to the CI system.
  - `build`: changes to the build system (we don't yet have one so this shouldn't apply).
  - `chore`: for other changes that don't match previous types. This doesn't appear
    in the changelog.

- `scope`: section of the codebase that the commit makes changes to. If it makes changes to
  many sections, or if no section in particular is modified, leave blank without the parentheses.
  Examples:

  - Commit that changes add a new feature to the Engine-3D:
  ```
  feat(Pulgins): add support for Engine Plugins
  ```

  - Commit that changes some code style:
  ```
  style: fix inline declaration of arrays
  ```

- `subject`: a brief description of the changes. This will be displayed in the changelog. If you need
  to specify other details, you can use the commit body, but it won't be visible.

  Formatting tricks: the commit subject may contain:

  - Links to related issues or PRs by writing `#issue`. This will be highlighted by the changelog tool:
    ```
    feat(Pulgins): add support for Plugins (#1234)
    ```

  - Formatted inline code by using backticks: the text between backticks will also be highlighted by
    the changelog tool:
    ```
    feat(Pulgins): enable unexported `DEFAULT_PROXY` setting (#9774)
    ```

### Style

Try to keep the first commit line short. It's harder to do using this commit style but try to be
concise, and if you need more space, you can use the commit body. Try to make sure that the commit
subject is clear and precise enough that users will know what changed by just looking at the changelog.

----

## Support and Contact

If you have any questions or need assistance, refer to [SUPPORT.md](.github/SUPPORT.md) for contact information and support resources.
To see the list of people who have contributed to this project, check out [CONTRIBUTORS.md](CONTRIBUTORS.md).
