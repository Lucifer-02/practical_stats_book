const std = @import("std");
const median = @import("chap1.zig").median;

pub fn main() !void {
    // const data = [_]f32{ 1, 2, 3, 4 };
    // std.debug.print("Median of {d} is {d}\n", .{ data, median(@TypeOf(data[0]), &data) });
    std.debug.print("{d}", .{@as(f16, @floatFromInt(10)) / 3});
}
