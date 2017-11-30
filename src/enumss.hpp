//
// Created by moemen on 11/27/17.
//

#ifndef KINGSMEN_ENUMSS_H_H
#define KINGSMEN_ENUMSS_H_H

#include <bits/stdc++.h>

class Piece
{
public:
    /// @brief Default constructor.
    Piece() noexcept;

    /// @brief Constructs a Piece from a given int8_t.
    /// @param piece The int8_t.
    Piece(int8_t piece) noexcept;

    enum : int8_t
    {
        Pawn = 0, Knight = 1, Bishop = 2, Rook = 3, Queen = 4, King = 5
    };

    enum : int8_t
    {
        WhitePawn = 0, WhiteKnight = 1, WhiteBishop = 2, WhiteRook = 3, WhiteQueen = 4, WhiteKing = 5,
        BlackPawn = 6, BlackKnight = 7, BlackBishop = 8, BlackRook = 9, BlackQueen = 10, BlackKing = 11,
        Empty = 12, NoPiece = 13
    };

    /// @return The int8_t.
    operator int8_t() const noexcept;
    /// @return A reference to the int8_t.
    operator int8_t&() noexcept;

    /// @brief Debugging function, used for checking if the piece is well-defined.
    /// @return True if the piece is well-defined, false otherwise.
    bool isOk() const noexcept;

    /// @brief Debugging function, used for checking if the piece type is well-defined. Should only be called if the given piece represents a piecetype.
    /// @return True if the piece type is well-defined, false otherwise.
    bool pieceTypeIsOk() const noexcept;

    /// @brief Debugging function, used for checking if the piece is actually representing a _real_ piece.
    /// @return True if the piece is not empty or not defined, false otherwise.
    bool canRepresentPieceType() const noexcept;

    /// @brief Gets the piece type of the given piece. We assume that this piece is representing a piece (not a piece type) at the moment.
    /// @return The piece type.
    Piece getPieceType() const noexcept;

private:
    int8_t mPiece;
};

inline Piece::Piece() noexcept : mPiece(NoPiece)
{
};

inline Piece::Piece(int8_t piece) noexcept : mPiece(piece)
{
};

inline Piece::operator int8_t() const noexcept
{
    return mPiece;
}

inline Piece::operator int8_t&() noexcept
{
    return mPiece;
}

inline bool Piece::isOk() const noexcept
{
    return (mPiece >= Piece::WhitePawn && mPiece <= Piece::Empty);
}

inline bool Piece::canRepresentPieceType() const noexcept
{
    return (mPiece >= Piece::WhitePawn && mPiece <= Piece::BlackKing);
}

inline bool Piece::pieceTypeIsOk() const noexcept
{
    return (mPiece >= Piece::Pawn && mPiece <= Piece::King);
}

inline Piece Piece::getPieceType() const noexcept
{
    assert(canRepresentPieceType());
    return (mPiece % 6);
}

class Color
{
public:
    /// @brief Default constructor.
    Color() noexcept;

    /// @brief Constructs a Color from a given int8_t.
    /// @param color The int8_t.
    Color(int8_t color) noexcept;

    enum : int8_t
    {
        White = 0, Black = 1, NoColor = 2
    };

    /// @return The int8_t.
    operator int8_t() const noexcept;
    /// @return A reference to the int8_t.
    operator int8_t&() noexcept;

    /// @brief Used for flipping the color from white to black and vice versa.
    /// @return The flipped color.
    Color operator!() const noexcept;

    /// @brief Debugging function, used for checking if the color is well-defined.
    /// @return True if the color is well-defined, false otherwise.
    bool isOk() const noexcept;

private:
    int8_t mColor;
};

inline Color::Color() noexcept : mColor(NoColor)
{
};

inline Color::Color(int8_t color) noexcept : mColor(color)
{
};

inline Color::operator int8_t() const noexcept
{
    return mColor;
}

inline Color::operator int8_t&() noexcept
{
    return mColor;
}

inline Color Color::operator!() const noexcept
{
    // ! has a branch normally, in our case we can eliminate it by just using a xor since we only have two well-defined values.
    // And yes, the difference in speed could actually be noticed.
    return mColor ^ 1;
}

inline bool Color::isOk() const noexcept
{
    return (mColor == Color::Black || mColor == Color::White);
}

class Square
{
public:
    /// @brief Default constructor.
    Square() noexcept;

    /// @brief Constructs a Square from a given int. Should be int8_t but that causes a metric ton of warnings which require ugly fixes.
    /// @param square The int.
    Square(int square) noexcept;

    enum : int8_t
    {
        A1, B1, C1, D1, E1, F1, G1, H1,
        A2, B2, C2, D2, E2, F2, G2, H2,
        A3, B3, C3, D3, E3, F3, G3, H3,
        A4, B4, C4, D4, E4, F4, G4, H4,
        A5, B5, C5, D5, E5, F5, G5, H5,
        A6, B6, C6, D6, E6, F6, G6, H6,
        A7, B7, C7, D7, E7, F7, G7, H7,
        A8, B8, C8, D8, E8, F8, G8, H8,
        NoSquare
    };

    /// @return The int8_t.
    operator int8_t() const noexcept;
    /// @return A reference to the int8_t.
    operator int8_t&() noexcept;

    /// @brief Debugging function, used for checking if the square is well-defined.
    /// @return True if the square is well-defined, false otherwise.
    bool isOk() const noexcept;

private:
    int8_t mSquare;
};

inline Square::Square() noexcept : mSquare(NoSquare)
{
}

inline Square::Square(int square) noexcept : mSquare(static_cast<int8_t>(square))
{
}

inline Square::operator int8_t() const noexcept
{
    return mSquare;
}

inline Square::operator int8_t&() noexcept
{
    return mSquare;
}

inline bool Square::isOk() const noexcept
{
    return (mSquare >= Square::A1 && mSquare <= Square::H8);
}

/// @brief Used for calculating the file of a given square. Not inside the class above because we always don't have an instance of Square when we want to call this.
/// @param sq The square.
/// @return The file as a number, 0 for A-file, 1 for B-file and so on.
inline int file(Square sq) noexcept
{
    assert(sq.isOk());
    return (sq % 8);
}

/// @brief Used for calculating the rank of a given square. Here for the same reason as file.
/// @param sq The square.
/// @return The rank as a number, 0 for 1st rank, 1 for 2nd rank and so on.
inline int rank(Square sq) noexcept
{
    assert(sq.isOk());
    return (sq / 8);
}


#endif //KINGSMEN_ENUMSS_H_H
