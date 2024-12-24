#include "coarse_acquisition_code.h"

#include <cstring>
#include <iterator>
#include <stdexcept>

static const std::array G2S = {5,   6,    7,   8,   17,  18,  139, 140, 141, 251, 252, 254,  255, 256,  257, 258, 469,
                               470, 471,  472, 473, 474, 509, 512, 513, 514, 515, 516, 859,  860, 861,  862, 863, 950,
                               947, 948,  950, 67,  103, 91,  19,  679, 225, 625, 946, 638,  161, 1001, 554, 280, 710,
                               709, 775,  864, 558, 220, 397, 55,  898, 759, 367, 299, 1018, 729, 695,  780, 801, 788,
                               732, 34,   320, 327, 389, 407, 525, 405, 221, 761, 260, 326,  955, 653,  699, 422, 188,
                               438, 959,  539, 879, 677, 586, 153, 792, 814, 446, 264, 1015, 278, 536,  819, 156, 957,
                               159, 712,  885, 461, 248, 713, 126, 807, 279, 122, 197, 693,  632, 771,  467, 647, 203,
                               145, 175,  52,  21,  237, 235, 886, 657, 634, 762, 355, 1012, 176, 603,  130, 359, 595,
                               68,  386,  797, 456, 499, 883, 307, 127, 211, 121, 118, 163,  628, 853,  484, 289, 811,
                               202, 1021, 463, 568, 904, 670, 230, 911, 684, 309, 644, 932,  12,  314,  891, 212, 185,
                               675, 503,  150, 395, 345, 846, 798, 992, 357, 995, 877, 112,  144, 476,  193, 109, 445,
                               291, 87,   399, 292, 901, 339, 208, 711, 189, 263, 537, 663,  942, 173,  900, 30,  500,
                               935, 556,  373, 85,  652, 310};

CoarseAcquisitionCode::CoarseAcquisitionCode() : m_codes(G2S.size())
{
  int8_t g1[CHIPS_PER_MS];
  std::fill_n(g1, CHIPS_PER_MS, static_cast<int8_t>(0));
  int8_t reg[10];
  std::fill_n(reg, 10, static_cast<int8_t>(-1));

  // Generate all g1 signal chips based on the g1 feedback polynomial
  for (int i = 0; i < CHIPS_PER_MS; ++i)
  {
    g1[i] = reg[9];
    int8_t saveBit = reg[2] * reg[9];
    memmove(&reg[1], &reg[0], 9 * sizeof(int8_t));
    reg[0] = saveBit;
  }

  int8_t g2[CHIPS_PER_MS];
  std::fill_n(g2, CHIPS_PER_MS, static_cast<int8_t>(0));
  std::fill_n(reg, 10, static_cast<int8_t>(-1));

  // Generate all g2 signal chips based on the g2 feedback polynomial
  for (int i = 0; i < CHIPS_PER_MS; ++i)
  {
    g2[i] = reg[9];
    int8_t saveBit = reg[1] * reg[2] * reg[5] * reg[7] * reg[8] * reg[9];
    memmove(&reg[1], &reg[0], 9 * sizeof(int8_t));
    reg[0] = saveBit;
  }

  for (std::size_t prn = 0; prn < m_codes.size(); ++prn)
  {
    uint32_t g2shift = G2S[prn];

    // shift g2 code and copy into temporary ca code
    int8_t* code = m_codes[prn].data();
    memcpy(code, &g2[CHIPS_PER_MS - g2shift], g2shift * sizeof(int8_t));
    memcpy(&code[g2shift], &g2[0], (CHIPS_PER_MS - g2shift) * sizeof(int8_t));
    // now multiply temporary ca_code with g1 to form the final ca code
    for (uint32_t i = 0; i < CHIPS_PER_MS; ++i)
    {
      code[i] *= g1[i];
    }
  }
}

const int8_t* CoarseAcquisitionCode::code(uint32_t prn) const
{
  if (prn < 1 || prn > m_codes.size())
  {
    throw std::runtime_error("Invalid PRN in custom signal CA code");
  }
  return m_codes[prn - 1].data();
}
