#ifndef BENCHMARK_CHART_H
#define BENCHMARK_CHART_H

#include <stddef.h>

#define MAX_CHART_POINTS 100
#define MAX_CHART_CURVES 5

typedef struct {
    double x;
    double y;
} ChartPoint;

typedef struct {
    char label[32];
    ChartPoint points[MAX_CHART_POINTS];
    int num_points;
    char glyph;
} ChartCurve;

typedef struct {
    char title[64];
    char x_label[32];
    char y_label[32];
    ChartCurve curves[MAX_CHART_CURVES];
    int num_curves;
    int width;
    int height;
} AsciiChart;

/**
 * Initializes the ASCII chart with a title, labels, and dimensions.
 *
 * @param chart Pointer to the AsciiChart structure.
 * @param title Chart title.
 * @param x_label Label for the X-axis.
 * @param y_label Label for the Y-axis.
 * @param width Total width of the chart in character cells.
 * @param height Total height of the chart in character cells.
 */
void chart_init(AsciiChart* chart, const char* title, const char* x_label, const char* y_label, int width, int height);

/**
 * Adds a new curve to the chart.
 *
 * @param chart Pointer to the AsciiChart structure.
 * @param label Name of the curve (used in the legend).
 * @param glyph Character representation of the curve (e.g., '*', 'o').
 * @return The index of the added curve, or -1 if the maximum number of curves has been reached.
 */
int chart_add_curve(AsciiChart* chart, const char* label, char glyph);

/**
 * Adds a data point to a specific curve.
 *
 * @param chart Pointer to the AsciiChart structure.
 * @param curve_index Index of the curve to add the point to.
 * @param x X coordinate.
 * @param y Y coordinate.
 * @return 0 on success, -1 on failure (e.g., curve_index out of bounds or max points reached).
 */
int chart_add_point(AsciiChart* chart, int curve_index, double x, double y);

/**
 * Renders the chart into a character buffer.
 *
 * @param chart Pointer to the AsciiChart structure.
 * @param out_buf Output buffer to write the rendered ASCII text.
 * @param buf_size Size of the output buffer.
 */
void chart_render(const AsciiChart* chart, char* out_buf, int buf_size);

#endif // BENCHMARK_CHART_H
