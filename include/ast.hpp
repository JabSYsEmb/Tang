/**
 * @file
 * Define the Tang::AstNode and its associated/derivative classes.
 */

#ifndef TANG_AST_HPP
#define TANG_AST_HPP

#include <string>
#include "location.hh"
#include "program.hpp"

namespace Tang {
  class Program;

  /**
   * Base class for representing nodes of an Abstract Syntax Tree (AST).
   *
   * There will be *many* derived classes, each one conveying the syntactic
   * meaning of the code that it represents.
   */
  class AstNode {
  protected:
    /**
     * The generic constructor.  It should never be called on its own.
     *
     * @param loc The location associated with this node.
     */
    AstNode(Tang::location loc) : location {loc} {}

    /**
     * The location associated with this node.
     */
    Tang::location location;

  public:
    /**
     * The object destructor.
     */
    virtual ~AstNode();

    /**
     * Return a string that describes the contents of the node.
     */
    virtual std::string dump(std::string indent = "") const;

    /**
     * Compile the ast of the provided Tang::Program.
     */
    virtual void compile(Tang::Program & program) const;

    /**
     * Provide a copy of the AstNode (recursively, if appropriate).
     *
     * @return A pointer to a new AstNode that is a copy of the current
     *   AstNode.
     */
    virtual AstNode * makeCopy() const;
  };

  /**
   * An AstNode that represents an integer literal.
   *
   * Integers are represented by the `int64_t` type, and so are limited in
   * range by that of the underlying type.
   */
  class AstNodeInteger : public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param number The number to represent.
     * @param loc The location associated with the expression.
     * @location The location associated with this node.
     */
    AstNodeInteger(int64_t number, Tang::location loc) : AstNode(loc), val{number} {}

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The integer value being stored.
     */
    int64_t val;
  };

  /**
   * An AstNode that represents an float literal.
   *
   * Integers are represented by the `long double` type, and so are limited in
   * range by that of the underlying type.
   */
  class AstNodeFloat: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param number The number to represent.
     * @param loc The location associated with the expression.
     * @location The location associated with this node.
     */
    AstNodeFloat(double number, Tang::location loc) : AstNode(loc), val{number} {}

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The float value being stored.
     */
    double val;
  };

  /**
   * An AstNode that represents a "+" expression
   */
  class AstNodeAdd: public AstNode {
  public:
    /**
     * The constructor.
     *
     * @param lhs The left hand side expression.
     * @param rhs The right hand side expression.
     * @param loc The location associated with the expression.
     * @location The location associated with this node.
     */
    AstNodeAdd(AstNode * lhs, AstNode * rhs, Tang::location loc) : AstNode(loc), lhs{lhs}, rhs{rhs} {}

    virtual std::string dump(std::string indent = "") const override;
    virtual void compile(Tang::Program & program) const override;
    virtual AstNode * makeCopy() const override;

  private:
    /**
     * The left hand side expression.
     */
    AstNode * lhs;

    /**
     * The right hand side expression.
     */
    AstNode * rhs;
  };
}

#endif // TANG_AST_HPP

