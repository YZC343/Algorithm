#if __cplusplus < 201700L
#error "C++17 required"
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>
#include <cstddef>
#include <mutex>
#include <optional>

// ��������8�֣��������������0:Unknow
constexpr int BlockTypeVariantCount = 9;
// ������ת����
constexpr int BlockRotationCount = 4;
// ��Ϊ��һ��һ�в��ᳬ��4,ʹ�����ǿ����� 4*4 16����
// ѹ��һ���飬���ﲻЯ��ƫ����Ϣ�����ǰ�������ת��Ϣ
using ZipBlock = uint16_t;
// һ��ֻ��10�У���������Ҳ����ѹ��Ϊһ��10���ص���
// ����ȡ������������ u16
using LineMask = uint16_t;

// ��֪���ģ�һ��ֻ��10��
constexpr LineMask FULL = 0b1'111'111'111;
// ����֪��һ�飬һ��ֻ��10����
constexpr int ColumnBound = 10;
// ����Ԥ����4�еĿ��У����ڼ򻯴�����������
constexpr int BlockBound = 4;
// ��Ҫ�ĵ�ͼֻ��18��
constexpr int LineBound = 18;
// �����һ��ȫ1�ĵ��棬����ײ
constexpr int ExtraLine = 1;

// ����ڲ���ʾ
using BlockMask = std::array<LineMask, BlockBound>;
// ��ͼ���ڲ���ʾ
// 0 -> ȫ1����ײ����
// 1 - 18 ʵ���ܷŵĵط�
// 19 20 21 22 Ԥ����Ϊ����õĵط�
using MapMask = std::array<LineMask, LineBound + BlockBound + ExtraLine>;

class Block;
class BackMap;
class UserController;
// �����ǵ�����
enum class BlockType : uint8_t {
    One = 1,
    Two = 2,
    Corner = 3,
    Square = 4,
    LeftL = 5,
    RightL = 6,
    Column = 7,
    Cross = 8,
};

// clang-format off
static constexpr ZipBlock PreProcessedBlocks[BlockTypeVariantCount][BlockRotationCount] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {17, 3, 17, 3},
    {19, 35, 50, 49},
    {51, 51, 51, 51},
    {547, 116, 785, 23},
    {275, 71, 802, 113},
    {4369, 15, 4369, 15},
    {626, 626, 626, 626}
};
// clang-format on

// �ú������ڿ��ӻ�һ��
// ���ڵ���
std::string readable(LineMask mask, char color = 'H') {
    std::string result(ColumnBound, '.');
    for (int i = ColumnBound - 1; i >= 0; --i) {
        if (mask & 1) {
            result[i] = color;
        }
        mask >>= 1;
    }
    return result;
}

#if __cplusplus >= 202300L
#include <print>
std::string _block_type_as_str(BlockType type) {
    static constexpr std::string _name_list[BlockTypeVariantCount] = {
        "Unknown", "One", "Two", "Corner", "Square", "LeftL", "RightL", "Column", "Cross",
    };
    return _name_list[(int)type];
}
#endif

using LineArray = std::array<bool, ColumnBound>;
class LineProxy {
    friend Block;
    friend BackMap;
    LineMask const& ref;
    LineProxy(LineMask const& ref): ref(ref) {}
public:
    operator LineArray() const {
        LineArray a;
        for(int i = 0; i < ColumnBound;++i) {
            a[i] = this->operator[](i);
        } 
        return a;
    }
    bool operator[](int i) const {
        return (bool)((ref >> (ColumnBound - i - 1)) & 1);
    }
};

// ��������
class Block {
    friend BackMap;
    friend UserController;
    BlockType btype;
    BlockMask mask;
    int rotation = 0;
    int x = 0;

    Block(BlockType type, int rotation = 0) : btype(type), rotation(rotation % BlockRotationCount) {
        (rotation += BlockRotationCount) %= BlockRotationCount;
        std::fill(mask.begin(), mask.end(), 0);
        do_unzip_on(type, rotation, mask);
    }
    // ��Ԥѹ���ķ����ѹ��BlockMask��
    static void do_unzip_on(BlockType tp, int rotation, BlockMask& mask) {
        ZipBlock blk = PreProcessedBlocks[(int)tp][rotation];
        for (int i = 0; i < BlockBound; ++i) {
            mask[i] = blk & 0b1111;
            blk >>= BlockBound;
        }
    }
    // ���λ���ĸ�������...
    static int hbit(LineMask mask) {
        return mask == 0 ? -1 : std::__lg(mask);
    }
    // ���λ���ĸ�������...
    static int lbit(LineMask mask) {
        mask = mask & -mask;
        return mask == 0 ? 10 : std::__lg(mask);
    }
    void sent() const {
        std::cout << (int)btype << " " << rotation << " " << x << std::endl;
    }

    // �÷�������˵��±�
    int lbound_inner() const {
        int res = -1;
        for (int i = 0; i < BlockBound; ++i) {
            res = std::max(res, hbit(mask[i]));
        }
        return res;
    }
    // �÷������Ҷ˵��±�
    int rbound_inner() const {
        int res = 10;
        for (int i = 0; i < BlockBound; ++i) {
            res = std::min(res, lbit(mask[i]));
        }
        return res;
    }

    int move_inner(int dx) {
        int left = lbound_inner();
        int right = rbound_inner();
        // [0,10)
        if (left + dx >= 10 || right + dx < 0)
            return false;
        x += dx;
        if (dx > 0) {
            for (int i = 0; i < BlockBound; ++i) {
                mask[i] <<= dx;
            }
        } else {
            dx = -dx;
            for (int i = 0; i < BlockBound; ++i) {
                mask[i] >>= dx;
            }
        }
        return true;
    }
public:
    // ����90��Ȼ��λ
    void rotate(int step = 1) {
        rotation = (rotation + step) % BlockRotationCount;
        do_unzip_on(btype, rotation, mask);
        x = 0;
    }
    void rotate_as(int r = 0) {
        rotation = r % BlockRotationCount;
        do_unzip_on(btype, rotation, mask);
        x = 0;
    }
    // �÷�������˵��±�
    int lbound() const {
        return ColumnBound - 1 - lbound_inner();
    }
    // �÷������Ҷ˵��±�
    int rbound() const {
        return ColumnBound - 1 - rbound_inner();
    }
    BlockType type() const {
        return btype;
    }
    Block remake_with(int r = 0) const {
        Block new_b {*this};
        new_b.rotate_as(r);
        return new_b;
    }
    // �飬�ƶ�.
    // �����ƶ� dx, ���ҽ���û��ð��10��Լ��ʱ���� true
    bool move(int dx) {
        return move_inner(-dx);
    }
    // ����һ����Ӧ���Ͷ�Ӧ��ת��ʽ�Ŀ�
    static Block make(BlockType type, int rotation = 0) {
        return Block(type, rotation);
    }

    int get_rotation() const {
        return rotation;
    }
    int get_x() const {
        return -x;
    }
    
    LineProxy operator[](int i) const {
        return LineProxy(mask[i]);
    }
};

class BackMap {
    friend Block;
    friend UserController;
    MapMask plain;
    int score = 0;
    static constexpr int bonus[] = {0, 1, 3, 6, 10};
    bool alive = true;
    bool is_preview = false;

    int remove_detect() {
        int h = 1, removed = 0;
        for (int cur = 1; cur < LineBound + ExtraLine + BlockBound; ++cur) {
            if (plain[cur] == FULL) {
                plain[cur] = 0;
                ++removed;
            }

            if (plain[h] != 0) {
                ++h;
                continue;
            }

            plain[h] = plain[cur];
            plain[cur] = 0;
            if (plain[h] != 0) {
                ++h;
                continue;
            }
        }
        score += bonus[removed];
        return removed;
    }

    bool alive_detect() {
        int h = LineBound + ExtraLine;
        for (int i = 0; i < BlockBound; ++i) {
            alive = alive && (plain[h + i] == 0);
        }
        return alive;
    }
    void grow(LineMask mask) {
        mask &= FULL;
        assert(mask != FULL);
        if (!alive) {
            return;
        }

        for (int i = LineBound + BlockBound; i > 1; --i) {
            plain[i] = plain[i - 1];
        }
        plain[1] = mask;
        alive = alive_detect();
    }

    BackMap() {
        plain.fill(0);
        plain[0] = FULL;
    }
    // ȷ������
    int assume(Block const& block) {
        if (!alive) {
            return 0;
        }
        if (!is_preview) {
            block.sent();
        }
        int h = LineBound + ExtraLine;
        // �����ײ
        for (; h > 0; --h) {
            bool hit = false;
            for (int i = 0; i < BlockBound; ++i) {
                hit = hit || ((plain[h + i] & block.mask[i]) != 0);
            }
            if (hit) {
                break;
            }
        }
        ++h;
        // ���÷���
        for (int i = 0; i < BlockBound; ++i) {
            plain[h + i] |= block.mask[i];
        }
        // �������
        int removed = remove_detect();
        // �����
        alive = alive_detect();
        return removed;
    }
public:
    LineProxy operator[](int i) const {
        return LineProxy(plain[i]);
    }
    
    // ��...���ڶ��ٷ���
    int current_score() const {
        return score;
    }
    // ��������������飬�ᷢ��ʲô��
    BackMap preview(Block const& block) const {
        BackMap ret{*this};
        ret.is_preview = true;
        ret.assume(block);
        return ret;
    }
    BackMap preview_rc(Block const& block, int & removed_count) const {
        BackMap ret{*this};
        ret.is_preview = true;
        removed_count = ret.assume(block);
        return ret;
    }
    
    // ��...���ڻ�������
    bool is_alive() const {
        return alive;
    }
    // ��߲�
    int max_layer() const {
        for(int i = 22; ; --i) {
            if (plain[i] != 0) {
                return i;
            }
        }
    }
};

class BlockList {
    friend UserController;
    std::deque<BlockType> types;
    BlockList(): types() {}
    void update() {
        int n = 0;
        std::cin >> n;
        int t;
        for (int i = 0; i < n; ++i) {
            std::cin >> t;
            types.emplace_back((BlockType)t);
        }
    }
    // ��rotation��ת��ʽ�ó���һ����
    Block next_with(int rotation = 0) {
        BlockType t = types.front();
        types.pop_front();
        return Block::make(t, rotation);
    }
    void pop() {
        types.pop_front();
    }
    public:

    // ͵����i�������
    BlockType peek(int i = 0) const {
        return types.at(i);
    }

    size_t size() const {
        return types.size();
    }

    Block operator[](int i) const {
        return Block::make(peek(i));
    }
};

class UserController {
    bool reset = false;
    inline static bool only_one = false;
    inline static std::mutex mtx = {};
    BackMap playground;
    BlockList blocklist;
    std::optional<Block> unctrlb = std::nullopt;
    void do_reset() {
        playground = BackMap();
        blocklist = BlockList();
        reset = false;
        // std::cout << "0 0 0" << std::endl;
    }
    bool update_inner() {
        reset = reset || !playground.is_alive();
        if (reset) {
            reason = "";
            do_reset();
        }
        unctrlb = std::nullopt;
        int n = 0, mask;
        std::cin >> n;
        for (int i = 0; i < n; ++i) {
            std::cin >> mask;
            playground.grow(mask);
        }
        blocklist.update();
        std::cin >> n;
        // 0xh1h2h3
        // h1 -> ��־λ
        //  0: ���·���
        //  1: ���ܿ�
        //  2: ����
        // h2 -> ��ת����
        // h3 -> ƫ�ƾ���
        mask = n >> (2 * 4);
        if (mask == 0) {
            if (reset) {
                reason = "Reset";
            }
            return !reset;
        }
        if (mask == 0xF) {
            reset = true;
            reason = "0xF";
            return false;
        }
        assert(mask == 0x1);
        mask = (n >> 4) & 0xF;
        Block b = blocklist.next_with(mask);
        b.move_inner(n & 0xF);
        unctrlb = b;
        playground.is_preview = true;
        playground.assume(b);
        playground.is_preview = false;
        reset = !playground.is_alive();
        if (reset) {
            reason = "Die";
        }
        return !reset;
    }
public:
    UserController() : playground(), blocklist() {
        if (only_one) {
            throw "Man What Can I Say";
        }
        mtx.lock();
        if (only_one) {
            mtx.unlock();
            throw "Man What Can I Say";
        }
        only_one = true;
        mtx.unlock();
    }
    bool is_finished() const {
        return reset;
    }
    std::string reason;
    // ���������״̬
    bool update() {
        bool f = update_inner();
        if (!f) {
            std::cout << "0 0 0" << std::endl;
        } 
        return f;
    }
    BlockList const& blocks() const {
        return blocklist;
    }
    BackMap const& map() const {
        return playground;
    }
    
    bool is_last_uc() const {
        return unctrlb.has_value();
    }

    std::optional<Block>const& ucblock() const {
        return unctrlb;
    }
    
    void operator << (Block const & b) {
        blocklist.pop();
        playground.assume(b);
    }
};

struct Game {
    BackMap const&map;
    BlockList const&blocks;
    std::optional<Block>const& ucblock;
    Block once_place();
    Game(UserController const&ctl) : map(ctl.map()),blocks(ctl.blocks()),ucblock(ctl.ucblock()) {
    }
};

/* ����Ը����������µĴ����� */

// �޸�����������Խ��з��þ���
// ע�⣬����һ���ṹ�巽��
// ����Է��ʽṹ��ģ� 
// map �ֶλ�ȡ��ͼ
// blocks �ֶλ�ȡ�󱸶���
// ucblock �ֶλ�ȡ��һ�β����󣬲������Ƿ��½��˲��ܿؿ鼰������

int evaluate(const BackMap& map, int removed);
int count_holes(const BackMap& map);

Block Game::once_place() {
    Block best_block = blocks[0];
    int best_score = -10000;

    // 尝试所有旋转状态
    for (int rot = 0; rot < BlockRotationCount; ++rot) {
        Block b = blocks[0].remake_with(rot);

        // 尝试所有可能的位置
        for (int pos = 0; pos <= ColumnBound - (b.rbound() - b.lbound() + 1); ++pos) {
            Block test = b;
            test.move(pos - b.lbound());

            // 预览下落结果
            int removed;
            BackMap preview = map.preview_rc(test, removed);

            // 计算分数
            int score = evaluate(preview, removed);

            if (score > best_score) {
                best_score = score;
                best_block = test;
            }
        }
    }

    return best_block;
}

int evaluate(const BackMap& map, int removed) {
    // 简单的评估函数
    int score = removed * 100;  // 消除行奖励

    // 惩罚高度
    int max_height = map.max_layer();
    score -= max_height * 10;

    // 惩罚孔洞
    int holes = count_holes(map);
    score -= holes * 50;

    return score;
}

int count_holes(const BackMap& map) {
    int holes = 0;
    // 实现计算孔洞数量的逻辑
    // ...
    return holes;
}

/* ���ǲ�Ҫ�޸� main ���� */

int main() {
    UserController systemctl;
    for(;;) {
        Game game(systemctl);
        while (systemctl.update()) {
            systemctl << game.once_place();
        }
    }
}
