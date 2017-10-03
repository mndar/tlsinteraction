#ifndef _surveillance_tls_interaction_h_
#define _surveillance_tls_interaction_h_
#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>


G_BEGIN_DECLS

G_DECLARE_FINAL_TYPE(SurveillanceTlsInteraction, surveillance_tls_interaction, SURVEILLANCE_TLS, INTERACTION, GTlsInteraction)

#define SURVEILLANCE_TLS_INTERACTION (surveillance_tls_interaction_get_type ())

SurveillanceTlsInteraction *surveillance_tls_interaction_new (GTlsCertificate*, GTlsCertificate *);

G_END_DECLS

#endif

