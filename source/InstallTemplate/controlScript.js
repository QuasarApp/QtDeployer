function Component(){}

Component.prototype.isDefault = function() {
    return true;
}

Component.prototype.createOperations = function() {
    console.log("create icons");

    try {
        component.createOperations();
    } catch (e) {
        print(e);
    }

    var name = installer.value("AppName");

    if (systemInfo.kernelType === "winnt" ) {
        console.log("create icons winnt");

        component.addOperation("CreateShortcut",
                               "@TargetDir@/" + name + ".exe",
                               "@DesktopDir@/" + name + ".lnk");
    }

    if (systemInfo.kernelType === "linux")
    {
        console.log("create icons linux");


        var targetDir = installer.value("TargetDir");
        var version = installer.value("Version");
        var homeDir = installer.value("HomeDir");
        var desktopFileTarget = installer.value("HomeDir") + "/.local/share/applications";
        var iconName = "%0";

        var res = installer.execute(targetDir + "/CreateDesktopEntry.sh", ["install", targetDir, name, version, iconName]);

        console.log(res);
    }
}
