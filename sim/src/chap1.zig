const std = @import("std");
const testing = std.testing;
const assert = std.debug.assert;

pub fn mean(comptime T: type, data: []const T) f64 {
    assert(data.len > 0);

    var sum: f64 = 0;

    switch (T) {
        i32 => for (data) |value| {
            sum += @as(f32, @floatFromInt(value));
        },

        f32 => for (data) |value| {
            sum += value;
        },

        else => @panic("Not support this type!"),
    }
    return sum / @as(f32, @floatFromInt(data.len));
}

test "test mean 1" {
    try testing.expect(mean(f32, &[_]f32{ 1, 2, 3 }) == 2);
}

test "test mean 2" {
    try testing.expect(mean(f32, &[_]f32{ 1, 2 }) == 1.5);
}
