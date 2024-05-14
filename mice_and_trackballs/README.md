## Elecom Deft Pro trackball

/etc/udev/hwdb.d/40-elecom-deft-pro.hwdb

The id in the .hwdb file is constructed with the bus, vendor and product codes that can be found with `evtest`. Each field is 4 characters.

After modifying the file, run these commands:
```
sudo udevadm hwdb --update
sudo udevadm trigger
```

```
gsettings set org.gnome.desktop.peripherals.trackball scroll-wheel-emulation-button 9
```

Optional, to make the scroll button a toggle:
```
gsettings set org.gnome.desktop.peripherals.trackball scroll-wheel-emulation-button-lock true
```

