function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to actually install README.txt!
    component.createOperations();

    if (!component.isUninstalled()) {
        console.log("remove icons!!!");

        if (systemInfo.kernelType === "winnt") {
            console.log("create icons!!! on Windows");
            component.addOperation("Delete",
                                   "@DesktopDir@/@Name@.lnk");
        }

        console.log("remove icons!!!");

        if (systemInfo.kernelType === "linux") {

            console.log("create icons!!! on LINUX");
            component.addOperation("Delete",
                                   "@HomeDir@/.local/share/applications/@Name@.desktop");
            component.addOperation("Delete",
                                   "@HomeDir@/Desktop/@Name@.desktop");

            console.log("remove icons!!! on LINUX done");
        }

    } else {
        console.log("create icons!!!");

        if (systemInfo.kernelType === "winnt") {
            console.log("create icons!!! on Windows");
            component.addOperation("CreateShortcut",
                                   "@TargetDir@/@Name@.exe",
                                   "@DesktopDir@/@Name@.lnk");
        }

        console.log("create icons!!!");

        if (systemInfo.kernelType === "linux") {
            console.log("create icons!!! on LINUX");
            component.addOperation("CreateDesktopEntry",
                                   "@HomeDir@/.local/share/applications/@Name@.desktop",
                                   "Version=@Version@\nType=Application\nTerminal=false\nExec=@TargetDir@/@Name@.sh\nName=@Name@\nIcon=@TargetDir@/%0\nName[en_US]=@Name@");

            console.log("create icons!!! on LINUX done");
        }
    }
}
