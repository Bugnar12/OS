int p[2];
pipe(p);
dup2(p[1], 2)
