const changeFormWifiSTA = () => {
  if (!document.getElementById("check_wifi").checked) {
    document.getElementById("ssidSTA").disabled = true;
    document.getElementById("passSTA").disabled = true;
    document.getElementById("IPsta").disabled = true;

    document.getElementById("ssidSTA").value = "";
    document.getElementById("passSTA").value = "";
    document.getElementById("IPsta").value = "";
  } else {
    document.getElementById("ssidSTA").disabled = false;
    document.getElementById("passSTA").disabled = false;
    document.getElementById("IPsta").disabled = false;
  }
};

changeFormWifiSTA();

document
  .getElementById("check_wifi")
  .addEventListener("change", changeFormWifiSTA);
