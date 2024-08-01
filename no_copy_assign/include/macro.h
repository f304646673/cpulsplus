# ifndef NO_COPY_ASSIGN_MACRO_H
# define NO_COPY_ASSIGN_MACRO_H

#define CPP_DISABLE_COPY(...) \
  __VA_ARGS__(const __VA_ARGS__ &) = delete; \
  __VA_ARGS__ & operator=(const __VA_ARGS__ &) = delete;

# endif // NO_COPY_ASSIGN_MACRO_H