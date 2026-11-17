let patients = JSON.parse(localStorage.getItem("patients")) || [];

const form = document.getElementById("patientForm");
const tableBody = document.getElementById("tableBody");
const searchBox = document.getElementById("search");

function save() {
  localStorage.setItem("patients", JSON.stringify(patients));
}

function render(list = patients) {
  tableBody.innerHTML = "";
  if (list.length === 0) {
    tableBody.innerHTML = '<tr><td colspan="6">No records found.</td></tr>';
    return;
  }
  list.forEach(p => {
    const row = document.createElement("tr");
    row.innerHTML = `
      <td>${p.id}</td>
      <td>${p.name}</td>
      <td>${p.age}</td>
      <td>${p.gender}</td>
      <td>${p.disease}</td>
      <td><button class="delete-btn" onclick="deletePatient(${p.id})">Delete</button></td>`;
    tableBody.appendChild(row);
  });
}

form.addEventListener("submit", e => {
  e.preventDefault();
  const id = Number(document.getElementById("pid").value);
  if (patients.some(p => p.id === id)) {
    alert("ID already exists!");
    return;
  }
  patients.push({
    id,
    name: document.getElementById("name").value,
    age: document.getElementById("age").value,
    gender: document.getElementById("gender").value,
    disease: document.getElementById("disease").value
  });
  save();
  render();
  form.reset();
});

function deletePatient(id) {
  patients = patients.filter(p => p.id !== id);
  save();
  render();
}

searchBox.addEventListener("input", () => {
  const q = searchBox.value.toLowerCase();
  render(patients.filter(p =>
    String(p.id).includes(q) || p.name.toLowerCase().includes(q)
  ));
});

render();
document.getElementById("logoutBtn").addEventListener("click", () => {
  sessionStorage.removeItem("loggedIn");
  window.location.href = "login.html";
});
document.getElementById("whoami").textContent =
  sessionStorage.getItem("currentUser") || "";