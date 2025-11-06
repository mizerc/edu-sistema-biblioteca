# Sistema Biblioteca

Application for managing book loans in libraries.

# 2025 Update

This is a large, monolithic, text-only C99 application designed to manage book loans.
It was originally created in 2011 and last updated in 2012 for a programming study case.

Originally created in 2011 and last updated in 2012.

The system was first developed for Windows, then later adapted for macOS through macro-based portability flags. 

A lot of improvement work to do here. This is super low priority, but I revisit it sometimes just for fun and to play with the old C language.

## Branches

- original => Contains the original files from 2012.
- main => Contains a few improvements added later on.

## Future Improvements

- Split the monolithic source into smaller, modular files
- Add OS-specific wrappers
- Reduce OS-specific behavior where possible (e.g., prefer fgets instead of getch)
- Use function(void) rather than function()