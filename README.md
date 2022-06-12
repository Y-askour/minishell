# minishell

## Pipeline: 
… | … creates two subshells, one for the left-hand side and one for the right-hand side, and waits for both to terminate. The shell creates a pipe and connects the left-hand side's standard output to the write end of the pipe and the right-hand side's standard input to the read end. In some shells (ksh88, ksh93, zsh, bash with the lastpipe option set and effective), the right-hand side runs in the original shell, so the pipeline construct only creates one subshell.
