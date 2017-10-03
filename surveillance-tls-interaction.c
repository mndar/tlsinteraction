#include "surveillance-tls-interaction.h"

//This struct should contain instance variable for the subclass
struct _SurveillanceTlsInteraction {
  GTlsInteraction parent_instance;
  GTlsCertificate *ca_cert, *client_cert_key;
};

G_DEFINE_TYPE(SurveillanceTlsInteraction, surveillance_tls_interaction, G_TYPE_TLS_INTERACTION)

//This function handles all initialisation
static void surveillance_tls_interaction_init (SurveillanceTlsInteraction *tls_interaction) {
}

gboolean accept_tls_certificate (GTlsConnection *conn, GTlsCertificate *peer_cert,
                             GTlsCertificateFlags errors, gpointer user_data) {
  GTlsCertificate *ca_tls_cert = (GTlsCertificate *) user_data;
  g_debug ("Entered accept_certificate");
  guint verification = g_tls_certificate_verify (peer_cert, NULL, ca_tls_cert);
  g_debug ("Accept Certificate: %d", verification);
  //Return TRUE or FALSE here depending on the value of verification
  return TRUE;
}

GTlsInteractionResult surveillance_request_certificate (GTlsInteraction *interaction,
                                                        GTlsConnection *connection,
                                                        GTlsCertificateRequestFlags flags,
                                                        GCancellable *cancellable,
                                                        GError **error) {
  SurveillanceTlsInteraction *stls = (SurveillanceTlsInteraction *) interaction;
  g_debug ("Surveillance Request Certificate");   
  g_signal_connect (connection, "accept-certificate", G_CALLBACK (accept_tls_certificate), stls->ca_cert);
  g_tls_connection_set_certificate (connection, stls->client_cert_key);
  return G_TLS_INTERACTION_HANDLED;
} 

//Virt funcs overrides, properties, signal defs here
static void surveillance_tls_interaction_class_init (SurveillanceTlsInteractionClass *class)
{
  GTlsInteractionClass *object_class = G_TLS_INTERACTION_CLASS (class);
  object_class->request_certificate = surveillance_request_certificate;
}

SurveillanceTlsInteraction * surveillance_tls_interaction_new (GTlsCertificate *client_cert_key, GTlsCertificate *ca_cert) {
  SurveillanceTlsInteraction *interaction = g_object_new (SURVEILLANCE_TLS_INTERACTION, NULL);
  interaction->client_cert_key = client_cert_key;
  interaction->ca_cert = ca_cert;
  return interaction;
}

