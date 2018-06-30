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

    console.log("create icons!!!");

    if (systemInfo.kernelType === "linux") {

        console.log("create icons!!! on LINUX");

        installer.performOperation("CreateDesktopEntry",
                               "@HomeDir@/.local/share/applications/@Name@.desktop",
                               "Version=@Version@\n
                                Type=Application\n
                                Terminal=false\n
                                Exec=@TargetDir@/@Name@.sh\n
                                Name=@Name@\n
                                Icon=@TargetDir@/bin/%0\n
                                Name[en_US]=YourApp_name");

//        installer.addElevatedOperation("Copy",
//                                       "@HomeDir@/.local/share/applications/@Name@.desktop",
//                                       "@HomeDir@/Desktop/@Name@.desktop");

        console.log("create icons!!! on LINUX done");

    }
}


Controller.prototype.uninstallationFinished = function()
{

}



