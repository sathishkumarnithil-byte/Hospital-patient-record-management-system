// List of allowed users. Edit or add more lines here anytime.
const USERS = [
  { id: "Nithil",  password: "Nithil@123" },
  { id: "Niwin", password: "Niwin@123"    },
  { id: "Vinith",  password: "Vinith@123" }
];

// If already logged in, skip straight to the main page
if (sessionStorage.getItem("loggedIn") === "true") {
  window.location.href = "index.html";
}

document.getElementById("loginForm").addEventListener("submit", function (e) {
  e.preventDefault();
  const id = document.getElementById("userId").value.trim();
  const pw = document.getElementById("password").value;

  const match = USERS.find(u => u.id === id && u.password === pw);

  if (match) {
    sessionStorage.setItem("loggedIn", "true");
    sessionStorage.setItem("currentUser", match.id);
    window.location.href = "index.html";
  } else {
    document.getElementById("error").textContent = "Invalid ID or password.";
  }
});