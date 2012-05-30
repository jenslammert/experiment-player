/**
 * @file
 * Header file to include when using the \e ExperimentReader class.
 */

#ifndef __EXPERIMENT_READER_H
#define __EXPERIMENT_READER_H

#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define EXPERIMENT_TYPE_READER \
	(experiment_reader_get_type())
/**
 * Cast instance pointer to \e ExperimentReader
 *
 * @param obj Object to cast to \e ExperimentReader
 * @return \e obj casted to \e ExperimentReader
 */
#define EXPERIMENT_READER(obj) \
	(G_TYPE_CHECK_INSTANCE_CAST((obj), EXPERIMENT_TYPE_READER, ExperimentReader))
#define EXPERIMENT_READER_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_CAST((klass), EXPERIMENT_TYPE_READER, ExperimentReaderClass))
#define EXPERIMENT_IS_READER(obj) \
	(G_TYPE_CHECK_INSTANCE_TYPE((obj), EXPERIMENT_TYPE_READER))
#define EXPERIMENT_IS_READER_CLASS(klass) \
	(G_TYPE_CHECK_CLASS_TYPE((klass), EXPERIMENT_TYPE_READER))
#define EXPERIMENT_READER_GET_CLASS(obj) \
	(G_TYPE_INSTANCE_GET_CLASS((obj), EXPERIMENT_TYPE_READER, ExperimentReaderClass))

/** @private */
typedef struct _ExperimentReaderPrivate ExperimentReaderPrivate;

/**
 * \e ExperimentReader instance structure
 */
typedef struct _ExperimentReader {
	GObject parent_instance;	/**< Parent instance structure */

	ExperimentReaderPrivate *priv;	/**< @private */
} ExperimentReader;

/**
 * \e ExperimentReader class structure
 */
typedef struct _ExperimentReaderClass {
	GObjectClass parent_class;	/**< Parent class structure */
} ExperimentReaderClass;

/** @private */
GType experiment_reader_get_type(void);

/*
 * Callbacks
 */
/**
 * Type of function to use for \e topic callbacks.
 *
 * @param reader     \e ExperimentReader the information refers to
 * @param topic_id   Symbolic identifier of experiment \b topic
 * @param start_time Beginning of first \b contribution in \e topic (milliseconds)
 * @param data       Callback user data
 */
/** @todo Perhaps we should use CClosures */
typedef void (*ExperimentReaderTopicCallback)(ExperimentReader *reader,
					      const gchar *topic_id,
					      gint64 start_time,
					      gpointer data);

typedef struct {
	gint64	start_time;
	gchar	text[];
} ExperimentReaderContrib;

/*
 * API
 */
ExperimentReader *experiment_reader_new(const gchar *filename);

GList *experiment_reader_get_contributions_by_speaker(
	ExperimentReader		*reader,
	const gchar			*speaker);
GList *experiment_reader_get_contribution_by_time(
	GList				*contribs,
	gint64				timept);
void experiment_reader_free_contributions(
	GList				*contribs);

void experiment_reader_foreach_greeting_topic(
	ExperimentReader		*reader,
	ExperimentReaderTopicCallback	callback,
	gpointer			data);
void experiment_reader_foreach_exp_initial_narrative_topic(
	ExperimentReader		*reader,
	ExperimentReaderTopicCallback	callback,
	gpointer			data);
void experiment_reader_foreach_exp_last_minute_phase_topic(
	ExperimentReader		*reader,
	gint				phase,
	ExperimentReaderTopicCallback	callback,
	gpointer			data);
void experiment_reader_foreach_farewell_topic(
	ExperimentReader		*reader,
	ExperimentReaderTopicCallback	callback,
	gpointer			data);

G_END_DECLS

#endif
