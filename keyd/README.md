Tries to mimic the QMK layout of my keyboards for the laptop.

Edit the configuration:
```
sudo vi /etc/keyd/default.conf
```

Reload configuration
```
sudo keyd reload
```

Check the log for errors:
```
sudo journalctl -eu keyd
```

---

Layout help: `]` + `\`. Press the same combo or `q` to dismis the popup.

Compose is on the *Extend* and *Nav* layers on the `AltGr` key.


