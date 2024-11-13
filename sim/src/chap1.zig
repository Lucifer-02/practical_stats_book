const std = @import("std");
const testing = std.testing;
const assert = std.debug.assert;
const expect = std.testing.expect;
const eql = std.mem.eql;

pub fn mean(comptime T: type, data: []const T) f64 {
    assert(data.len > 0); // not accept empty data

    var sum: f64 = 0;

    switch (T) {
        i16, i32, i64 => for (data) |value| {
            sum += @as(f32, @floatFromInt(value));
        },

        f16, f32, f64 => for (data) |value| {
            sum += value;
        },

        else => @panic("Not support this type!"),
    }

    return sum / @as(f32, @floatFromInt(data.len));
}

pub fn trimmedMean(comptime T: type, data: []T, trim: usize) f64 {
    assert(data.len > trim * 2); // the trimming not over data length
    const allocator = std.heap.page_allocator;

    const copy = allocator.alloc(T, data.len) catch {
        @panic("Out of memory");
    };
    defer allocator.free(copy);
    @memcpy(copy, data);

    std.mem.sort(T, data[0..], {}, comptime std.sort.asc(T));

    const trimmed_data = data[trim..(data.len - trim)];
    assert(trimmed_data.len == (data.len - 2 * trim));

    return mean(T, trimmed_data);
}

test "test mean 1" {
    const data = [_]f32{ 1, 2, 3 };
    try testing.expect(mean(f32, &data) == 2);
}

test "test mean 2" {
    const data = [_]f32{ 1, 2 };
    try testing.expect(mean(f32, &data) == 1.5);
}

test "test mean 3" {
    const data = [_]i32{ 1, 2 };
    try testing.expect(mean(i32, &data) == 1.5);
}

test "test trimmed mean 1" {
    var data = [_]i32{ 0, 1, 2, 0 };
    try testing.expect(trimmedMean(i32, &data, 1) == 0.5);
}

test "test trimmed mean 2" {
    var data = [_]f16{ 0, 1.5, 2, 0 };
    try testing.expect(trimmedMean(@TypeOf(data[0]), &data, 1) == 0.75);
}

test "test trimmed mean 3" {
    var data = [_]f16{ 0, 1, 2, 1, 3 };
    try testing.expect(trimmedMean(@TypeOf(data[0]), &data, 2) == 1);
}
