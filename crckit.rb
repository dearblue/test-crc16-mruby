#! ruby

module CRCKit
  def CRCKit.build_table(bitwidth, polynomial, slicebits, sliderounds)
    bitoff = bitwidth - slicebits
    table = []
    elements = 1 << slicebits
    bitwindow = (1 << bitwidth) - 1

    table << elements.times.map { |i|
      i <<= bitoff
      slicebits.times {
        i <<= 1
        i ^= polynomial unless i[bitwidth].zero?
      }
      i & bitwindow
    }

    (1...sliderounds).step {
      table << elements.times.map { |i|
        n = table[-1][i]
        bitwindow & (n << slicebits) ^ table[0][n >> bitoff]
      }
    }

    table
  end

  def CRCKit.generate_code(table)
    <<-"CRCTABLE"
#include <stdint.h>

static const uint16_t table[#{table.size}][#{table[0].size}] =
{
  #{
    table.each_with_object("").with_index { |(t, s), r|
      s << "\n  " if r > 0
      s << "{ /* round #{r} */\n"
      t.each_slice(8).with_index { |tt, i|
        s << "\n" unless i == 0
        s << "    "
        s << tt.map { |e| "0x%04xU," % e }.join(" ")
      }
      s << "\n  },"
    }
  }
};
    CRCTABLE
  end

  def CRCKit.bitreflect(n, bitsize:)
    m = 0
    bitsize.times { m <<= 1; m |= n[0]; n >>= 1 }
    m
  end

  #
  # Computes r * x ** N mod p(x)
  #
  # ref: https://github.com/rawrunprotected/crc
  #
  def CRCKit.exp_mod33(n, p, r)
    p &= 0xffffffff
    r &= 0xffffffff

    n.times do
      r = ((r & 0x7fffffff) << 1) ^ (p & -(r >> 31))
    end
    r
  end

  #
  # Computes r * x ** N mod p(x)
  #
  # ref: https://github.com/rawrunprotected/crc
  #
  def CRCKit.exp_mod65(n, p, r)
    p &= 0xffffffffffffffff
    r &= 0xffffffffffffffff

    n.times do
      r = ((r & 0x7fffffffffffffff) << 1) ^ (p & -(r >> 63))
    end
    r
  end

  #
  # Computes x ** 65 / p(x); the result has an implicit 65th bit.
  #
  # ref: https://github.com/rawrunprotected/crc
  #
  def CRCKit.div129by65(p)
    q = 0
    h = p
    for i in 0...64
      q |= h[63] << (63 - i)
      h = ((h & 0x7fffffffffffffff) << 1) ^ (p & -h[63])
    end
    q
  end

  def CRCKit.div65by33(p)
    q = 0
    h = p
    for i in 0...32
      q |= h[31] << (31 - i)
      h = ((h & 0x7fffffff) << 1) ^ (p & -h[31])
    end
    q
  end
end

#CRCKit.generate_code(CRCKit.build_table(16, 0x1021, 4, 16))
