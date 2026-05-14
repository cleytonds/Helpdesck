# TODO_AUTH_REFACTOR.md

## Auth/UserRepository circular dependency refactor

- [ ] 1) Update `backend/include/repositories/UserRepository.hpp`
  - align constructor/signatures
  - define `MYSQL* conn_` member
  - remove `resetPasswordByToken` from repository API (unless required)

- [ ] 2) Update `backend/src/repositories/UserRepository.cpp`
  - remove incompatible/legacy implementations (e.g. `create(const User&)`)
  - implement only the exact header signatures
  - ensure `conn_` member name/type matches header

- [ ] 3) Update `backend/include/services/AuthService.hpp`
  - reduce includes using forward declarations where possible
  - keep signatures consistent with cpp

- [ ] 4) Update `backend/src/services/AuthService.cpp`
  - ensure it compiles with new UserRepository API
  - remove any dependency on removed repository methods

- [ ] 5) Build verification: run `mingw32-make` and fix remaining errors

