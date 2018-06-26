function Controller()
{
    installer.uninstallationFinished.connect(this, Controller.prototype.uninstallationFinished);
    installer.installationFinished.connect(this, Controller.prototype.installationFinished);
}

Controller.prototype.installationFinished = function()
{

    if (systemInfo.kernelType === "winnt") {
        component.addOperation("CreateShortcut",
                               "@TargetDir@/@Name@.exe",
                               "@DesktopDir@/@Name@.lnk");
    }

    if (systemInfo.kernelType === "linux") {
        component.addOperation("CreateDesktopEntry",
                               "@HomeDir@/.local/share/applications/@Name@.desktop",
                               "Version=@Version@\n
                                Type=Application\n
                                Terminal=false\n
                                Exec=@TargetDir@/@Name@.sh\n
                                Name=@Name@\n
                                Icon=@TargetDir@/bin/%0\n
                                Name[en_US]=YourApp_name");

        component.addElevatedOperation("Copy",
                                       "@HomeDir@/.local/share/applications/@Name@.desktop",
                                       "@HomeDir@/Desktop/@Name@.desktop");
    }
}


Controller.prototype.uninstallationFinished = function()
{

}



