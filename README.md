# tlsinteraction
GLib TLS Interaction Example

A TLS Interaction object tested with GStreamer's rtspsrc, souphttpsrc and rtspclientsink.



A simple example
----------------
Prepare two GTLSCertificate *: 
1. my_tls_cert: your TLS certificate that the server will verify
2. ca_tls_cert: the CA's TLS certificate which you use in accept_tls_certificate to verify the server's certificate.


#include "surveillance-tls-interaction.h"

...

...

SurveillanceTlsInteraction *interaction = surveillance_tls_interaction_new (my_tls_cert, ca_tls_cert);

g_object_set (rtspclientsink, "tls-interaction", interaction, NULL);

...

...

