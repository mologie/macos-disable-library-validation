DisableLibraryValidation
========================

*DO NOT INSTALL THIS SOFTWARE ON YOUR MACHINE.* It intentionally weakens the security of your Mac and may turn your machine into a fire-breathing dragon.

With that out of the way: This software installs a small kernel patch at boot-time, which disables [Library Validation](https://developer.apple.com/library/content/documentation/Security/Conceptual/CodeSigningGuide/Procedures/Procedures.html#//apple_ref/doc/uid/TP40005929-CH4-SW9). Library Validation exists independently of SIP and cannot be disabled without a kernel patch.

You don't want Library Validation to be disabled on your Mac. However, if it were to be disabled:

* Processes can load arbitrary libraries
* root becomes more powerful (may load arbitrary libraries into any process depending on SIP status)
* The NVIDIA web driver won't break iBooks and other software that accesses its libraries directly
* Security is weakened, because some user processes could be fooled to run additional code without root's explicit request, which may grant access to daemons that depend on Library Validation for secure validation of code identity.

Installation
------------

Install Xcode, then `./install.sh`.

On success, you should see a message from 'DisableLibraryValidation' in the output of `sudo dmesg` and find 'com.apple.kext.mologie.DisableLibraryValidation' in the output of `kextstat`.

The patches take effect immediately, but you might have to restart processes that are broken by Library Validation (such as iBooks with the NVIDIA Web Drivers.)

Removal
-------

`sudo ./install.sh uninstall`

Bug Reports
-----------

This software comes with no support or implied warrenty. I do not accept bug reports, but I welcome pull requests that fix bugs should you have found any. You may also submit pull requests for adding information to this readme file.

Legal
-----

Copyright 2017 Oliver Kuckertz; released under the [MIT license](LICENSE). Please contact me privately via the e-mail address listed on my GitHub profile for discussing legal issues.
