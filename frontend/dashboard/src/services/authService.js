import api from "./api";

// ===============================
// LOGIN
// ===============================
export const loginRequest = (data) => {
  return api.post("/login", data);
};

// ===============================
// REGISTER
// ===============================
export const registerRequest = (data) => {
  return api.post("/register", data);
};

// ===============================
// FORGOT PASSWORD
// ===============================
export const forgotPasswordRequest = (email) => {
  return api.post("/forgot-password", {
    email,
  });
};

// ===============================
// RESET PASSWORD
// ===============================
export const resetPasswordRequest = (token, newPassword) => {
  return api.post("/reset-password", {
    token,
    newPassword,
  });
};