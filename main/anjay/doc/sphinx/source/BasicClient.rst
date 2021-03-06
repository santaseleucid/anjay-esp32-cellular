..
   Copyright 2017-2021 AVSystem <avsystem@avsystem.com>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

Basic client
============

In this tutorial we will focus on creating simple LwM2M Client based on Anjay
library, featuring:

- secure connection to a LwM2M Server,
- Object with writable and readable resources.

This client can be a good starting point for creating more complex applications.

.. toctree::
   :glob:
   :titlesonly:

   BasicClient/BC-Initialization
   BasicClient/BC-MandatoryObjects
   BasicClient/BC-Security
   BasicClient/BC-ObjectImplementation
   BasicClient/BC-Notifications
   BasicClient/BC-Send
   BasicClient/BC-ThreadSafety
