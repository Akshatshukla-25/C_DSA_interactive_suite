#include "benchmark_chart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void draw_line(char* grid, int width, int x0, int y0, int x1, int y1, char glyph,
                      int left_margin, int plot_width, int top_margin, int plot_height)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        if (x0 >= left_margin && x0 < left_margin + plot_width &&
            y0 >= top_margin && y0 < top_margin + plot_height)
        {
            grid[y0 * width + x0] = glyph;
        }

        if (x0 == x1 && y0 == y1)
        {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void chart_init(AsciiChart* chart, const char* title, const char* x_label, const char* y_label, int width, int height)
{
    memset(chart, 0, sizeof(AsciiChart));
    snprintf(chart->title, sizeof(chart->title), "%s", title);
    snprintf(chart->x_label, sizeof(chart->x_label), "%s", x_label);
    snprintf(chart->y_label, sizeof(chart->y_label), "%s", y_label);
    chart->width = width;
    chart->height = height;
    chart->num_curves = 0;
}

int chart_add_curve(AsciiChart* chart, const char* label, char glyph)
{
    if (chart->num_curves >= MAX_CHART_CURVES)
    {
        return -1;
    }
    int idx = chart->num_curves++;
    snprintf(chart->curves[idx].label, sizeof(chart->curves[idx].label), "%s", label);
    chart->curves[idx].glyph = glyph;
    chart->curves[idx].num_points = 0;
    return idx;
}

int chart_add_point(AsciiChart* chart, int curve_index, double x, double y)
{
    if (curve_index < 0 || curve_index >= chart->num_curves)
    {
        return -1;
    }
    ChartCurve* curve = &chart->curves[curve_index];
    if (curve->num_points >= MAX_CHART_POINTS)
    {
        return -1;
    }
    int idx = curve->num_points++;
    curve->points[idx].x = x;
    curve->points[idx].y = y;
    return 0;
}

void chart_render(const AsciiChart* chart, char* out_buf, int buf_size)
{
    if (chart->width <= 0 || chart->height <= 0 || buf_size <= 0)
    {
        if (buf_size > 0)
        {
            out_buf[0] = '\0';
        }
        return;
    }

    char* grid = malloc(chart->height * chart->width);
    if (!grid)
    {
        out_buf[0] = '\0';
        return;
    }
    memset(grid, ' ', chart->height * chart->width);

    int left_margin = 10;
    int right_margin = 2;
    int top_margin = 2;
    int bottom_margin = 4;

    int plot_width = chart->width - left_margin - right_margin;
    int plot_height = chart->height - top_margin - bottom_margin;

    if (plot_width <= 0 || plot_height <= 0)
    {
        free(grid);
        out_buf[0] = '\0';
        return;
    }

    // 1. Calculate limits
    double min_x = 0, max_x = 0;
    double min_y = 0, max_y = 0;
    int first = 1;

    for (int c = 0; c < chart->num_curves; c++)
    {
        const ChartCurve* curve = &chart->curves[c];
        for (int p = 0; p < curve->num_points; p++)
        {
            double x = curve->points[p].x;
            double y = curve->points[p].y;
            if (first)
            {
                min_x = max_x = x;
                min_y = max_y = y;
                first = 0;
            }
            else
            {
                if (x < min_x) min_x = x;
                if (x > max_x) max_x = x;
                if (y < min_y) min_y = y;
                if (y > max_y) max_y = y;
            }
        }
    }

    if (first)
    {
        min_x = 0;
        max_x = 10;
        min_y = 0;
        max_y = 10;
    }
    else
    {
        if (min_y > 0)
        {
            min_y = 0; // force Y axis to start at 0 for visual reference
        }
        if (max_x == min_x)
        {
            max_x = min_x + 1.0;
        }
        if (max_y == min_y)
        {
            max_y = min_y + 1.0;
        }
    }

    // 2. Draw lines and points
    for (int c = 0; c < chart->num_curves; c++)
    {
        const ChartCurve* curve = &chart->curves[c];
        for (int p = 0; p < curve->num_points; p++)
        {
            double x = curve->points[p].x;
            double y = curve->points[p].y;

            int px = 0;
            if (max_x > min_x)
            {
                px = (int)((x - min_x) / (max_x - min_x) * (plot_width - 1) + 0.5);
            }
            int py = 0;
            if (max_y > min_y)
            {
                py = (int)((y - min_y) / (max_y - min_y) * (plot_height - 1) + 0.5);
            }

            int gx = left_margin + px;
            int gy = top_margin + (plot_height - 1 - py);

            if (p > 0)
            {
                double prev_x = curve->points[p - 1].x;
                double prev_y = curve->points[p - 1].y;
                int prev_px = 0;
                if (max_x > min_x)
                {
                    prev_px = (int)((prev_x - min_x) / (max_x - min_x) * (plot_width - 1) + 0.5);
                }
                int prev_py = 0;
                if (max_y > min_y)
                {
                    prev_py = (int)((prev_y - min_y) / (max_y - min_y) * (plot_height - 1) + 0.5);
                }
                int prev_gx = left_margin + prev_px;
                int prev_gy = top_margin + (plot_height - 1 - prev_py);

                draw_line(grid, chart->width, prev_gx, prev_gy, gx, gy, curve->glyph,
                          left_margin, plot_width, top_margin, plot_height);
            }

            if (gx >= left_margin && gx < left_margin + plot_width &&
                gy >= top_margin && gy < top_margin + plot_height)
            {
                grid[gy * chart->width + gx] = curve->glyph;
            }
        }
    }

    // 3. Draw axes
    for (int r = 0; r < plot_height; r++)
    {
        int y = top_margin + r;
        grid[y * chart->width + (left_margin - 1)] = '|';
    }
    for (int col = 0; col < plot_width; col++)
    {
        int x = left_margin + col;
        grid[(top_margin + plot_height) * chart->width + x] = '-';
    }
    grid[(top_margin + plot_height) * chart->width + (left_margin - 1)] = '+';

    // 4. Draw labels & ticks
    grid[top_margin * chart->width + (left_margin - 1)] = '+';
    grid[(top_margin + plot_height / 2) * chart->width + (left_margin - 1)] = '+';
    grid[(top_margin + plot_height - 1) * chart->width + (left_margin - 1)] = '+';

    char label_buf[32];
    int len, start_col;

    // Y Max label
    snprintf(label_buf, sizeof(label_buf), "%8.3g", max_y);
    len = strlen(label_buf);
    start_col = (left_margin - 1) - len;
    if (start_col < 0) start_col = 0;
    for (int i = 0; i < len && (start_col + i) < (left_margin - 1); i++)
    {
        grid[top_margin * chart->width + start_col + i] = label_buf[i];
    }

    // Y Mid label
    snprintf(label_buf, sizeof(label_buf), "%8.3g", min_y + (max_y - min_y) / 2.0);
    len = strlen(label_buf);
    start_col = (left_margin - 1) - len;
    if (start_col < 0) start_col = 0;
    for (int i = 0; i < len && (start_col + i) < (left_margin - 1); i++)
    {
        grid[(top_margin + plot_height / 2) * chart->width + start_col + i] = label_buf[i];
    }

    // Y Min label
    snprintf(label_buf, sizeof(label_buf), "%8.3g", min_y);
    len = strlen(label_buf);
    start_col = (left_margin - 1) - len;
    if (start_col < 0) start_col = 0;
    for (int i = 0; i < len && (start_col + i) < (left_margin - 1); i++)
    {
        grid[(top_margin + plot_height - 1) * chart->width + start_col + i] = label_buf[i];
    }

    // X axis ticks
    grid[(top_margin + plot_height) * chart->width + left_margin] = '+';
    grid[(top_margin + plot_height) * chart->width + left_margin + plot_width / 2] = '+';
    grid[(top_margin + plot_height) * chart->width + left_margin + plot_width - 1] = '+';

    // X Min label
    snprintf(label_buf, sizeof(label_buf), "%.3g", min_x);
    for (int i = 0; i < (int)strlen(label_buf) && (left_margin + i) < chart->width; i++)
    {
        grid[(top_margin + plot_height + 1) * chart->width + left_margin + i] = label_buf[i];
    }

    // X Mid label
    snprintf(label_buf, sizeof(label_buf), "%.3g", min_x + (max_x - min_x) / 2.0);
    len = strlen(label_buf);
    int start_x_mid = left_margin + plot_width / 2 - len / 2;
    for (int i = 0; i < len && (start_x_mid + i) < chart->width; i++)
    {
        grid[(top_margin + plot_height + 1) * chart->width + start_x_mid + i] = label_buf[i];
    }

    // X Max label
    snprintf(label_buf, sizeof(label_buf), "%.3g", max_x);
    len = strlen(label_buf);
    int start_x = left_margin + plot_width - len;
    if (start_x < left_margin) start_x = left_margin;
    for (int i = 0; i < len && (start_x + i) < chart->width; i++)
    {
        grid[(top_margin + plot_height + 1) * chart->width + start_x + i] = label_buf[i];
    }

    // 5. Titles & labels
    // Title
    int title_len = strlen(chart->title);
    int title_start = (chart->width - title_len) / 2;
    if (title_start < 0) title_start = 0;
    for (int i = 0; i < title_len && (title_start + i) < chart->width; i++)
    {
        grid[0 * chart->width + title_start + i] = chart->title[i];
    }

    // Y Axis label
    int yl_len = strlen(chart->y_label);
    for (int i = 0; i < yl_len && i < chart->width; i++)
    {
        grid[1 * chart->width + i] = chart->y_label[i];
    }

    // X Axis label
    int xl_len = strlen(chart->x_label);
    int xl_start = left_margin + (plot_width - xl_len) / 2;
    if (xl_start < 0) xl_start = 0;
    for (int i = 0; i < xl_len && (xl_start + i) < chart->width; i++)
    {
        grid[(top_margin + plot_height + 2) * chart->width + xl_start + i] = chart->x_label[i];
    }

    // Legend
    char legend_buf[512] = "Legend: ";
    for (int c = 0; c < chart->num_curves; c++)
    {
        char entry[64];
        snprintf(entry, sizeof(entry), "[%c] %s   ", chart->curves[c].glyph, chart->curves[c].label);
        strncat(legend_buf, entry, sizeof(legend_buf) - strlen(legend_buf) - 1);
    }
    int leg_len = strlen(legend_buf);
    int leg_start = (chart->width - leg_len) / 2;
    if (leg_start < 0) leg_start = 0;
    for (int i = 0; i < leg_len && (leg_start + i) < chart->width; i++)
    {
        grid[(chart->height - 1) * chart->width + leg_start + i] = legend_buf[i];
    }

    // Write to output buffer
    int idx = 0;
    for (int r = 0; r < chart->height; r++)
    {
        for (int c = 0; c < chart->width; c++)
        {
            if (idx < buf_size - 2)
            {
                out_buf[idx++] = grid[r * chart->width + c];
            }
        }
        if (idx < buf_size - 2)
        {
            out_buf[idx++] = '\n';
        }
    }
    out_buf[idx] = '\0';

    free(grid);
}
