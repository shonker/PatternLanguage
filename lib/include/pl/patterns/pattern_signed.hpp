#pragma once

#include <pl/patterns/pattern.hpp>

namespace pl {

    class PatternSigned : public Pattern {
    public:
        PatternSigned(Evaluator *evaluator, u64 offset, size_t size, u32 color = 0)
            : Pattern(evaluator, offset, size, color) { }

        [[nodiscard]] std::unique_ptr<Pattern> clone() const override {
            return std::unique_ptr<Pattern>(new PatternSigned(*this));
        }

        i128 getValue() {
            i128 data = 0;
            this->getEvaluator()->readData(this->getOffset(), &data, this->getSize());
            data = pl::changeEndianess(data, this->getSize(), this->getEndian());

            return pl::signExtend(this->getSize() * 8, data);
        }

        [[nodiscard]] std::string getFormattedName() const override {
            switch (this->getSize()) {
                case 1:
                    return "s8";
                case 2:
                    return "s16";
                case 4:
                    return "s32";
                case 8:
                    return "s64";
                case 16:
                    return "s128";
                default:
                    return "Signed data";
            }
        }

        [[nodiscard]] bool operator==(const Pattern &other) const override { return areCommonPropertiesEqual<decltype(*this)>(other); }

        void accept(PatternVisitor &v) override {
            v.visit(*this);
        }
    };

}