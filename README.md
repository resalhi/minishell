# minishell
This project is about creating a simple shell (bash).

Available options

Minishell runs executables from an absolute, relative or environment PATH (/bin/ls or ls), including arguments or options. ' and " work the same as bash, except for multiline commands.

You can use redirections (> >> <), herdoc (<<) and pipes |.

Environment variables are handled, like ($HOME), including the return code ($?).

Finally, you can use Ctrl-C to interrupt as well as Ctrl-D, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for : echo, pwd, cd, env, export, unset and exit.

Credit

This two-person project was done with https://github.com/MbarekManouze .

I was responsible for the parsing, environment variables, built-in functions and signal handling.

mmanouze took care of the execution, redirections, herdoc and piping.
