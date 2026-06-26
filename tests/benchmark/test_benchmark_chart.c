#include "benchmark_chart.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_chart_init(void)
{
    AsciiChart chart;
    chart_init(&chart, "Test Title", "X Axis", "Y Axis", 80, 24);
    assert(strcmp(chart.title, "Test Title") == 0);
    assert(strcmp(chart.x_label, "X Axis") == 0);
    assert(strcmp(chart.y_label, "Y Axis") == 0);
    assert(chart.width == 80);
    assert(chart.height == 24);
    assert(chart.num_curves == 0);
    printf("test_chart_init passed.\n");
}

void test_chart_add_curve(void)
{
    AsciiChart chart;
    chart_init(&chart, "Test Title", "X Axis", "Y Axis", 80, 24);

    int idx1 = chart_add_curve(&chart, "Curve 1", '*');
    assert(idx1 == 0);
    assert(chart.num_curves == 1);
    assert(strcmp(chart.curves[idx1].label, "Curve 1") == 0);
    assert(chart.curves[idx1].glyph == '*');

    int idx2 = chart_add_curve(&chart, "Curve 2", 'o');
    assert(idx2 == 1);
    assert(chart.num_curves == 2);

    // Add up to MAX_CHART_CURVES
    for (int i = 2; i < MAX_CHART_CURVES; i++)
    {
        int idx = chart_add_curve(&chart, "Dummy", 'x');
        assert(idx == i);
    }

    // Try to add one more
    int idx_fail = chart_add_curve(&chart, "OverLimit", '!');
    assert(idx_fail == -1);

    printf("test_chart_add_curve passed.\n");
}

void test_chart_add_point(void)
{
    AsciiChart chart;
    chart_init(&chart, "Test Title", "X Axis", "Y Axis", 80, 24);
    int c_idx = chart_add_curve(&chart, "Curve 1", '*');

    int status1 = chart_add_point(&chart, c_idx, 10.0, 100.0);
    assert(status1 == 0);
    assert(chart.curves[c_idx].num_points == 1);
    assert(chart.curves[c_idx].points[0].x == 10.0);
    assert(chart.curves[c_idx].points[0].y == 100.0);

    int status_fail = chart_add_point(&chart, 99, 10.0, 100.0);
    assert(status_fail == -1);

    printf("test_chart_add_point passed.\n");
}

void test_chart_render(void)
{
    AsciiChart chart;
    chart_init(&chart, "Complexity Growth Comparison", "Input Size (N)", "Time (ms)", 80, 24);

    int c1 = chart_add_curve(&chart, "O(N)", '*');
    int c2 = chart_add_curve(&chart, "O(N^2)", 'x');

    for (int i = 1; i <= 5; i++)
    {
        double n = i * 20.0;
        chart_add_point(&chart, c1, n, n);        // linear
        chart_add_point(&chart, c2, n, n * n / 2.0); // quadratic
    }

    char buf[4096];
    chart_render(&chart, buf, sizeof(buf));

    assert(strlen(buf) > 0);
    // Verify it contains the titles and axis markings
    assert(strstr(buf, "Complexity Growth Comparison") != NULL);
    assert(strstr(buf, "Input Size (N)") != NULL);
    assert(strstr(buf, "Time (ms)") != NULL);
    assert(strstr(buf, "Legend:") != NULL);

    // Verify it contains the curve glyphs
    assert(strchr(buf, '*') != NULL);
    assert(strchr(buf, 'x') != NULL);

    // Output rendered chart for visual inspection
    printf("\nRendered Chart Output:\n%s\n", buf);
    printf("test_chart_render passed.\n");
}

int main(void)
{
    printf("Running Core ASCII Chart Engine Tests...\n");
    test_chart_init();
    test_chart_add_curve();
    test_chart_add_point();
    test_chart_render();
    printf("All Core ASCII Chart Engine Tests passed successfully!\n");
    return 0;
}
